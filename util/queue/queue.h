#ifndef QUEUE_H
#define QUEUE_H

/**
 * Queue node alias.
 */
typedef struct _queue_node queue_node_t;

/**
 * Queue alias.
 */
typedef struct _queue queue_t;

/**
 * Allocates memory to an empty queue.
 *
 * @return pointer to {@link queue_t}.
 */
queue_t *queue_create();

/**
 * Allocates memory to a queue node that contains the specified data.
 *
 * @param data pointer that the node will to point.
 * @return pointer to {@link queue_node_t}.
 */
queue_node_t *queuenode_create(void *data);

/**
 * Puts data at end of the queue.
 *
 * @param queue queue to do the operation.
 * @param data pointer to the data that will be putted at end of the queue.
 */
void queue_enqueue(queue_t *queue, void *data);

/**
 * Removes data from begin of the queue.
 *
 * @param queue queue to do the operation.
 * @return pointer to the data removed from begin of the queue.
 */
void* queue_dequeue(queue_t *queue);

/**
 * Checks if the queue has no data.
 *
 * @param queue queue to do the operation.
 * @return 1 if has no data or 0 otherwise.
 */
int queue_is_empty(queue_t *queue);

/**
 * Traverses the queue returning the data.
 *
 * @param queue where to do the operation.
 * @param block pointer to function that receives the data of the queue.
 */
void queue_iterate(queue_t *queue, void (*block)(void *data));

#endif
