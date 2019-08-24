#include <stdio.h>
#include <stdlib.h>
#include "priority_queue.h"

struct _queue {
    queue_node_t *head;
    queue_node_t *tail;
};

int should_swap_nodes(queue_node_t *node1, queue_node_t *node2, ORDER order);

void priority_queue_enqueue(queue_t *queue, void *data, int priority, ORDER order)
{
    queue_node_t *new_node = queuenode_create(data);
    new_node->priority = priority;

    if (queue_is_empty(queue) || should_swap_nodes(queue->head, new_node, order)) {
        new_node->next = queue->head;
        queue->head = new_node;
    } else {
        queue_node_t *node = queue->head;
        while (node->next != NULL && should_swap_nodes(new_node, node->next, order)) {
            node = node->next;
        }
        new_node->next = node->next;
        node->next = new_node;
    }
    if (new_node->next == NULL) {
        queue->tail = new_node;
    }
}

queue_node_t* priority_queue_dequeue(queue_t *queue)
{
    if (queue_is_empty(queue)) {
        return NULL;
    }
    queue_node_t *dequeued = queue->head;
    queue->head = dequeued->next;
    if (queue_is_empty(queue)) {
        queue->tail = NULL;
    }
    dequeued->next = NULL;
    return dequeued;
}

void priority_queue_iterate(queue_t *queue, void (*block)(void *data, int priority))
{
    queue_node_t *node = queue->head;
    while (node != NULL) {
        block(node->data, node->priority);
        node = node->next;
    }
}

int should_swap_nodes(queue_node_t *node1, queue_node_t *node2, ORDER order)
{
    int priority1 = node1->priority;
    int priority2 = node2->priority;

    return (order == ASC && priority1 >= priority2) || (order == DESC && priority1 <= priority2);
}
