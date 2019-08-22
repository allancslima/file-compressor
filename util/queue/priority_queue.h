#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include "queue.h"

typedef enum order { ASC, DESC } ORDER;

/**
 * Puts data according the priority value in crescent or descending order.
 *
 * @param queue queue to do the operation.
 * @param data pointer to the data that will be putted at end of the queue.
 * @param priority integer value, a lower value means lower priority and a bigger value means bigger priority.
 * If already there the priority on the queue, the last added data gets bigger priority.
 */
void priorityqueue_enqueue(queue_t *queue, void *data, int priority, ORDER order);

#endif
