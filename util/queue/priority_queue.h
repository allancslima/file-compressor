#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include "queue.h"

/**
 * Queue node struct.
 */
struct _queue_node {
    void *data;
    int priority;
    queue_node_t *next;
};

/**
 * The sort enumerator to queue items according a specified priority.
 * ASC to ascending order and DESC to descending order.
 */
typedef enum order { ASC, DESC } ORDER;

/**
 * Puts data according the priority value in crescent or descending order.
 *
 * @param queue queue to do the operation.
 * @param data pointer to the data that will be putted at end of the queue.
 * @param priority integer value, a lower value means lower priority and a bigger value means bigger priority.
 * If the priority already exists in the queue, the new data gets bigger priority.
 */
void priority_queue_enqueue(queue_t *queue, void *data, int priority, ORDER order);

/**
 * Removes node from begin of the queue.
 *
 * @param queue queue to do the operation.
 * @return pointer to the node removed from begin of the queue. The @{link _queue_node#next} field point to NULL.
 */
queue_node_t* priority_queue_dequeue(queue_t *queue);

/**
 * Traverses the queue returning the data and the priority.
 *
 * @param queue where to do the operation.
 * @param on_item pointer to function that receives the data and the priority of the queue node.
 */
void priority_queue_iterate(queue_t *queue, void (*on_item)(void *data, int priority));

#endif
