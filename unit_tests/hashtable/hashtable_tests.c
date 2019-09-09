#include <stdio.h>
#include <stdlib.h>
#include "CUnit/Basic.h"
#include "../../util/hashtable/hashtable.h"

hashtable_t *hashtable;

void should_put_key_value_pair()
{
    hashtable_t *hashtable = hashtable_create(5, sizeof(char*));
    char *string1 = "Data Structures\0";
    char *string2 = "IC - UFAL\0";

    hashtable_put(hashtable, 2, string1);
    hashtable_put(hashtable, 4, string2);

    CU_ASSERT_EQUAL(hashtable_get(hashtable, 2), string1);
    CU_ASSERT_EQUAL(hashtable_get(hashtable, 4), string2);
}

void should_update_value_on_existent_key_put()
{
    hashtable_t *hashtable = hashtable_create(5, sizeof(char*));
    char *string1 = "Data Structures\0";
    char *string2 = "IC - UFAL\0";

    hashtable_put(hashtable, 3, string1);
    hashtable_put(hashtable, 3, string2);

    CU_ASSERT_EQUAL(hashtable_get(hashtable, 3), string2);
}

void should_remove_value()
{
    hashtable_t *hashtable = hashtable_create(5, sizeof(char*));
    char *string = (char*) malloc(sizeof(char) * 20);
    strcpy(string, "Data Structures\0");

    hashtable_put(hashtable, 3, string);
    hashtable_remove(hashtable, 3);

    CU_ASSERT_FALSE(hashtable_contains_key(hashtable, 3));
}

void should_iterate_existent_key_value_pairs()
{
    hashtable_t *hashtable = hashtable_create(5, sizeof(char*));
    char *string1 = "Data Structures\0";
    char *string2 = "IC - UFAL\0";
    char *string3 = "Hashtable\0";
    char *string4 = "Huffman\0";

    hashtable_put(hashtable, 0, string1);
    hashtable_put(hashtable, 1, string2);
    hashtable_put(hashtable, 2, string3);
    hashtable_put(hashtable, 3, string4);

    void on_pair(int key, void *value)
    {
        switch (key) {
            case 0:
                CU_ASSERT_EQUAL(value, string1);
                break;
            case 1:
                CU_ASSERT_EQUAL(value, string2);
                break;
            case 2:
                CU_ASSERT_EQUAL(value, string3);
                break;
            default:
                CU_ASSERT_EQUAL(value, string4);
                break;
        }
    }

    hashtable_iterate(hashtable, on_pair);
}

int main()
{
    if (CUE_SUCCESS != CU_initialize_registry()) {
        return CU_get_error();
    }
    CU_pSuite pSuite = CU_add_suite("Hashtable", 0, 0);

    if (pSuite == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    if (CU_add_test(pSuite, "Put key-value pair", should_put_key_value_pair) == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    if (CU_add_test(pSuite, "Put on existent key", should_update_value_on_existent_key_put) == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    if (CU_add_test(pSuite, "Remove value", should_remove_value) == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    if (CU_add_test(pSuite, "Iterate existent key-value pairs", should_iterate_existent_key_value_pairs) == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    return CU_get_error();
}
