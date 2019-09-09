#include <stdio.h>
#include <stdlib.h>
#include "CUnit/Basic.h"
#include "../../util/tree/binary_tree.h"

void should_print_in_pre_order()
{
    char *pre_order = "**CB***FEDA\0";
    char asterisk = '*', c = 'C', b = 'B', f = 'F', e = 'E', d = 'D', a = 'A';

    binary_tree_t *c_leaf = binary_tree_create(&c, NULL, NULL);
    binary_tree_t *b_leaf = binary_tree_create(&b, NULL, NULL);
    binary_tree_t *f_leaf = binary_tree_create(&f, NULL, NULL);
    binary_tree_t *e_leaf = binary_tree_create(&e, NULL, NULL);
    binary_tree_t *d_leaf = binary_tree_create(&d, NULL, NULL);
    binary_tree_t *a_leaf = binary_tree_create(&a, NULL, NULL);

    binary_tree_t *tree = binary_tree_create(&asterisk,
            binary_tree_create(&asterisk, c_leaf, b_leaf),
            binary_tree_create(&asterisk,
                    binary_tree_create(&asterisk, binary_tree_create(&asterisk, f_leaf, e_leaf), d_leaf), a_leaf));

    char *pre_order_assert;

    void on_node(void *data)
    {
        int new_len = pre_order_assert == NULL ? 2 : strlen(pre_order_assert) + 2;
        pre_order_assert = (char*) realloc(pre_order_assert, sizeof(char) * new_len);
        pre_order_assert[new_len - 2] = *((char*) data);
        pre_order_assert[new_len - 1] = '\0';
    }

    binary_tree_pre_order_1(tree, on_node);
    CU_ASSERT_STRING_EQUAL(pre_order, pre_order_assert);
}

void should_be_leaf()
{
    int n = 1;
    binary_tree_t *tree = binary_tree_create(&n, NULL, NULL);

    CU_ASSERT(binary_tree_is_leaf(tree));
}

int main()
{
    if (CUE_SUCCESS != CU_initialize_registry()) {
        return CU_get_error();
    }
    CU_pSuite pSuite = CU_add_suite("Binary Tree", 0, 0);

    if (pSuite == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    if (CU_add_test(pSuite, "Print in pre order", should_print_in_pre_order) == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    if (CU_add_test(pSuite, "Be leaf", should_be_leaf) == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    return CU_get_error();
}
