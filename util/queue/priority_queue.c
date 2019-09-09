#include <stdio.h>
#include <stdlib.h>
#include "priority_queue.h"

struct _queue {
    int size;
    queue_node_t *head;
    queue_node_t *tail;
};

/**
 * Checks if a node should take the place of another node considering their priorities and queue order. This function
 * must be used when another node don't be at on beginning of queue.
 *
 * @param node1 node to compare regarding another node.
 * @param node2 the another node.
 * @param order queue order.
 * @return 1 if should take the place or 0 otherwise.
 */
int should_take_place(queue_node_t *node1, queue_node_t *node2, ORDER order);

/**
 * Checks if a node should take the place of another node considering their priorities and queue order. This function
 * must be used when another node is at on beginning of queue.
 *
 * @param node1 node to compare regarding another node.
 * @param node2 the another node.
 * @param order queue order.
 * @return 1 if should take the place or 0 otherwise.
 */
int should_take_place_at_beginning(queue_node_t *node1, queue_node_t *node2, ORDER order);


void priority_queue_enqueue(queue_t *queue, void *data, int priority, ORDER order)
{
    queue_node_t *new_node = queue_node_create(data);
    new_node->priority = priority;

    if (queue_is_empty(queue) || should_take_place_at_beginning(new_node, queue->head, order)) {
        new_node->next = queue->head;
        queue->head = new_node;
    } else {
        queue_node_t *node = queue->head;

        while (node->next != NULL && should_take_place(new_node, node->next, order)) {
            node = node->next;
        }
        new_node->next = node->next;
        node->next = new_node;
    }
    if (new_node->next == NULL) {
        queue->tail = new_node;
    }
    queue->size++;
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
    queue->size--;
    dequeued->next = NULL;
    return dequeued;
}

void priority_queue_iterate(queue_t *queue, void (*on_item)(void *data, int priority))
{
    queue_node_t *node = queue->head;
    while (node != NULL) {
        on_item(node->data, node->priority);
        node = node->next;
    }
}

void priority_queue_free(queue_t *queue)
{
    queue_node_t *head = queue->head;

    while (head != NULL) {
        free(head->data);
        queue_node_t *previous = head;
        head = head->next;
        free(previous);
    }
    free(queue);
}


int should_take_place(queue_node_t *node1, queue_node_t *node2, ORDER order)
{
    int priority1 = node1->priority;
    int priority2 = node2->priority;

    return (order == ASC && priority1 > priority2) || (order == DESC && priority1 < priority2);
}

int should_take_place_at_beginning(queue_node_t *node1, queue_node_t *node2, ORDER order)
{
    int priority1 = node1->priority;
    int priority2 = node2->priority;

    return (order == ASC && priority1 <= priority2) || (order == DESC && priority1 >= priority2);
}
