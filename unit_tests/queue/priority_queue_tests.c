#include <stdio.h>
#include <stdlib.h>
#include "CUnit/Basic.h"
#include "../../util/queue/priority_queue.h"

void should_enqueue_in_ascending_order()
{
    queue_t *queue = queue_create();
    char *first = "First\0";
    char *second = "Second\0";
    char *third = "Third\0";

    priority_queue_enqueue(queue, third, 3, ASC);
    priority_queue_enqueue(queue, first, 1, ASC);
    priority_queue_enqueue(queue, second, 2, ASC);

    CU_ASSERT_EQUAL(priority_queue_dequeue(queue)->data, first);
    CU_ASSERT_EQUAL(priority_queue_dequeue(queue)->data, second);
    CU_ASSERT_EQUAL(priority_queue_dequeue(queue)->data, third);
}

void should_enqueue_in_descending_order()
{
    queue_t *queue = queue_create();
    char *first = "First\0";
    char *second = "Second\0";
    char *third = "Third\0";

    priority_queue_enqueue(queue, third, 3, DESC);
    priority_queue_enqueue(queue, first, 1, DESC);
    priority_queue_enqueue(queue, second, 2, DESC);

    CU_ASSERT_EQUAL(priority_queue_dequeue(queue)->data, third);
    CU_ASSERT_EQUAL(priority_queue_dequeue(queue)->data, second);
    CU_ASSERT_EQUAL(priority_queue_dequeue(queue)->data, first);
}

void should_enqueue_last_with_bigger_priority_to_equals_priorities()
{
    queue_t *queue = queue_create();
    char *first = "First\0";
    char *second = "Second\0";
    char *third = "Third\0";

    priority_queue_enqueue(queue, first, 1, ASC);
    priority_queue_enqueue(queue, second, 1, ASC);
    priority_queue_enqueue(queue, third, 1, ASC);

    CU_ASSERT_EQUAL(priority_queue_dequeue(queue)->data, third);
    CU_ASSERT_EQUAL(priority_queue_dequeue(queue)->data, second);
    CU_ASSERT_EQUAL(priority_queue_dequeue(queue)->data, first);
}

void should_be_empty_after_dequeue_all()
{
    queue_t *queue = queue_create();
    char *first = "First\0";
    char *second = "Second\0";
    char *third = "Third\0";

    priority_queue_enqueue(queue, first, 1, ASC);
    priority_queue_enqueue(queue, second, 2, ASC);
    priority_queue_enqueue(queue, third, 3, ASC);
    priority_queue_dequeue(queue);
    priority_queue_dequeue(queue);
    priority_queue_dequeue(queue);

    CU_ASSERT(queue_is_empty(queue));
}

void should_return_NULL_on_dequeue_empty_queue()
{
    queue_t *queue = queue_create();
    char *first = "First\0";
    char *second = "Second\0";
    char *third = "Third\0";

    priority_queue_enqueue(queue, first, 1, ASC);
    priority_queue_enqueue(queue, second, 2, ASC);
    priority_queue_enqueue(queue, third, 3, ASC);
    priority_queue_dequeue(queue);
    priority_queue_dequeue(queue);
    priority_queue_dequeue(queue);

    CU_ASSERT_PTR_NULL(priority_queue_dequeue(queue));
}

int main()
{
    if (CUE_SUCCESS != CU_initialize_registry()) {
        return CU_get_error();
    }
    CU_pSuite pSuite = CU_add_suite("Priority Queue", 0, 0);

    if (pSuite == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    if (CU_add_test(pSuite, "Enqueue in ascending order", should_enqueue_in_ascending_order) == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    if (CU_add_test(pSuite, "Enqueue in descending order", should_enqueue_in_descending_order) == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    if (CU_add_test(pSuite, "Enqueue with same priorities",
            should_enqueue_last_with_bigger_priority_to_equals_priorities) == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    if (CU_add_test(pSuite, "Empty queue", should_be_empty_after_dequeue_all) == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    if (CU_add_test(pSuite, "Dequeue empty queue", should_return_NULL_on_dequeue_empty_queue) == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    return CU_get_error();
}
