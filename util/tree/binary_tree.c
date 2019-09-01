#include <stdio.h>
#include <stdlib.h>
#include "binary_tree.h"

binary_tree_t* binary_tree_create(void *data, binary_tree_t *left, binary_tree_t *right)
{
    binary_tree_t *binary_tree = (binary_tree_t*) malloc(sizeof(binary_tree_t));
    binary_tree->data = data;
    binary_tree->left = left;
    binary_tree->right = right;

    return binary_tree;
}

int binary_tree_size(binary_tree_t *binary_tree)
{
    if (binary_tree == NULL) {
        return 0;
    }
    return 1 + binary_tree_size(binary_tree->left) + binary_tree_size(binary_tree->right);
}

int binary_tree_is_leaf(binary_tree_t *binary_tree)
{
    return binary_tree != NULL && binary_tree->left == NULL && binary_tree->right == NULL;
}

void binary_tree_in_order(binary_tree_t *binary_tree, void (*block)(void *data))
{
    if (binary_tree != NULL) {
        binary_tree_in_order(binary_tree->left, block);
        block(binary_tree->data);
        binary_tree_in_order(binary_tree->right, block);
    }
}

void binary_tree_pre_order(binary_tree_t *binary_tree, void (*block)(void *data))
{
    if (binary_tree != NULL) {
        block(binary_tree->data);
        binary_tree_pre_order(binary_tree->left, block);
        binary_tree_pre_order(binary_tree->right, block);
    }
}

void binary_tree_post_order(binary_tree_t *binary_tree, void (*block)(void *data))
{
    if (binary_tree != NULL) {
        binary_tree_post_order(binary_tree->left, block);
        binary_tree_post_order(binary_tree->right, block);
        block(binary_tree->data);
    }
}
