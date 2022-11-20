#ifndef AVL_TREE_REIMPLEMENTED_AVL_TREE_H
#define AVL_TREE_REIMPLEMENTED_AVL_TREE_H
#include "BST.h"

int avl_node_balance_factor(Node* node);
int avl_is_node_balanced(Node* node);
int avl_is_every_node_balanced(Node* root);

void avl_rotate_right(Node** root);
void avl_rotate_left(Node** root);
void avl_rotate_rl(Node** root);
void avl_rotate_lr(Node** root);

void avl_insert(Node** root, int key); // wrapper function for bst_insert and avl_balance_tree
void avl_delete(Node** root, int key); // wrapper function for bst_delete and avl_balance_tree

void avl_balance_node(Node** node);
void avl_balance_tree(Node** root);

#endif //AVL_TREE_REIMPLEMENTED_AVL_TREE_H
