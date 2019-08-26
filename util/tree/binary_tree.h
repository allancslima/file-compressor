#ifndef BINARY_TREE_H
#define BINARY_TREE_H

/**
 * Binary tree alias.
 */
typedef struct _binary_tree binary_tree_t;

/**
 * Binary tree struct.
 */
struct _binary_tree {
    void *data;
    binary_tree_t *left;
    binary_tree_t *right;
};

/**
 * Allocates memory to a node containing pointers to the data, the left node and the right node.
 *
 * @param data pointer to the allocated data.
 * @param left left binary tree.
 * @param right right binary tree.
 * @return pointer to {@link binary_tree_t}
 */
binary_tree_t* binary_tree_create(void *data, binary_tree_t *left, binary_tree_t *right);

/**
 * Checks if the given binary tree is a leaf, that's it don't have children nodes.
 *
 * @param binary_tree pointer to a binary tree root.
 * @param block pointer to function that receives the data of the node tree.
 */
int is_leaf(binary_tree_t *binary_tree);

/**
 * Traverses binary tree from a root in normal order.
 *
 * @param binary_tree pointer to a binary tree root.
 * @param block pointer to function that receives the data of the node tree.
 */
void binary_tree_in_order(binary_tree_t *binary_tree, void (*block)(void *data));

/**
 * Traverses binary tree from a root in pre order.
 *
 * @param binary_tree pointer to a binary tree root.
 * @param block pointer to function that receives the data of the node tree.
 */
void binary_tree_pre_order(binary_tree_t *binary_tree, void (*block)(void *data));

/**
 * Traverses binary tree from a root in post order.
 *
 * @param binary_tree pointer to a binary tree root.
 * @param block pointer to function that receives the data of the node tree.
 */
void binary_tree_post_order(binary_tree_t *binary_tree, void (*block)(void *data));

#endif
