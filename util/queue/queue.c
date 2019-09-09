#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

struct _queue_node {
    void *data;
    int priority;
    queue_node_t *next;
};

struct _queue {
    int size;
    queue_node_t *head;
    queue_node_t *tail;
};

queue_t *queue_create()
{
    queue_t *new_queue = (queue_t*) malloc(sizeof(queue_t));
    new_queue->size = 0;
    new_queue->head = NULL;
    new_queue->tail = NULL;

    return new_queue;
}

queue_node_t* queue_node_create(void *data)
{
    queue_node_t *new_node = (queue_node_t*) malloc(sizeof(queue_node_t));
    new_node->data = data;
    new_node->priority = 0;
    new_node->next = NULL;

    return new_node;
}

void queue_enqueue(queue_t *queue, void *data)
{
    queue_node_t *new_node = queue_node_create(data);

    if (queue_is_empty(queue)) {
        queue->head = new_node;
        queue->tail = new_node;
    } else {
        queue->tail->next = new_node;
        queue->tail = new_node;
    }
    queue->size++;
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
    queue->size--;
    free(dequeued);
    return dequeued_data;
}

int queue_is_empty(queue_t *queue)
{
    return queue_size(queue) == 0;
}

int queue_size(queue_t *queue)
{
    return queue->size;
}

void queue_iterate(queue_t *queue, void (*on_item)(void *data))
{
    queue_node_t *node = queue->head;
    while (node != NULL) {
        on_item(node->data);
        node = node->next;
    }
}

void queue_free(queue_t *queue)
{
    void on_item(void *data)
    {
        free(data);
    }

    queue_iterate(queue, on_item);
    free(queue);
}
