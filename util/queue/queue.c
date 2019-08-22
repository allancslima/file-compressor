#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

queue_t *queue_create()
{
    queue_t *new_queue = (queue_t*) malloc(sizeof(queue_t));
    new_queue->head = NULL;
    new_queue->tail = NULL;

    return new_queue;
}

queue_node_t *queuenode_create(void *data)
{
    queue_node_t *new_node = (queue_node_t*) malloc(sizeof(queue_node_t));
    new_node->data = data;
    new_node->priority = 0;
    new_node->next = NULL;

    return new_node;
}

void queue_enqueue(queue_t *queue, void *data)
{
    queue_node_t *new_node = queuenode_create(data);

    if (queue_is_empty(queue)) {
        queue->head = new_node;
        queue->tail = new_node;
    } else {
        queue->tail->next = new_node;
        queue->tail = new_node;
    }
}

void* queue_dequeue(queue_t *queue)
{
    if (queue_is_empty(queue)) {
        return NULL;
    }
    queue_node_t *dequeued = queue->head;
    void *dequeued_data = dequeued->data;

    queue->head = dequeued->next;
    if (queue_is_empty(queue)) {
        queue->tail = NULL;
    }
    free(dequeued);
    return dequeued_data;
}

int queue_is_empty(queue_t *queue)
{
    return queue->head == NULL;
}

void queue_iterate(queue_t *queue, void (*block)(void *data))
{
    queue_node_t *node = queue->head;
    while (node != NULL) {
        block(node->data);
        node = node->next;
    }
}
