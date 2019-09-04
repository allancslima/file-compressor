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

void binary_tree_pre_order_1(binary_tree_t *binary_tree, void (*on_node)(void *data))
{
    if (binary_tree != NULL) {
        on_node(binary_tree->data);
        binary_tree_pre_order_1(binary_tree->left, on_node);
        binary_tree_pre_order_1(binary_tree->right, on_node);
    }
}

void binary_tree_pre_order_2(
        binary_tree_t *binary_tree,
        void (*on_internal_node)(void *data),
        void (*on_leaf)(void *data))
{
    if (binary_tree_is_leaf(binary_tree)) {
        on_leaf(binary_tree->data);
    } else {
        on_internal_node(binary_tree->data);
        binary_tree_pre_order_2(binary_tree->left, on_internal_node, on_leaf);
        binary_tree_pre_order_2(binary_tree->right, on_internal_node, on_leaf);
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
