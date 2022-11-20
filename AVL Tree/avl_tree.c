#include <stdio.h>
#include <stdlib.h>
#include "avl_tree.h"

/*-------------------HELPER FUNCTIONS-------------------*/

int avl_node_balance_factor(Node* node) {
  if(node == NULL) return 0;
  int height_diff = get_height(node->left) - get_height(node->right);
  return height_diff;
}

int avl_is_node_balanced(Node* node) {
  return abs(avl_node_balance_factor(node)) <= 1;
}

int avl_is_every_node_balanced(Node* root) {
  if(root == NULL) return 1;
  if(avl_is_node_balanced(root) == 0) return 0;
  return avl_is_every_node_balanced(root->left) && avl_is_every_node_balanced(root->right);
}

/*-------------------ROTATIONS-------------------*/

void avl_rotate_right(Node** root) {
  if(*root == NULL) return;
  Node* new_root = (*root)->left;
  (*root)->left = new_root->right;
  new_root->right = *root;
  *root = new_root;
}

void avl_rotate_left(Node** root) {
  if(*root == NULL) return;
  Node* new_root = (*root)->right;
  (*root)->right = new_root->left;
  new_root->left = *root;
  *root = new_root;
}

void avl_rotate_rl(Node** root) {
  avl_rotate_right(&(*root)->right);
  avl_rotate_left(root);
}

void avl_rotate_lr(Node** root) {
  avl_rotate_left(&(*root)->left);
  avl_rotate_right(root);
}

/*-------------------BALANCING-------------------*/

void avl_balance_node(Node** node) {
  if(avl_is_node_balanced(*node) == 1) return;
  int balance_factor = avl_node_balance_factor(*node);

  if(balance_factor > 1) { // Left heavy. either left-left or left-right
    if(avl_node_balance_factor((*node)->left) > 0) { // left-left
      avl_rotate_right(node);
      return;
    }
    avl_rotate_lr(node); // left-right
    return;
  }
  // right heavy. either right-right or right-left
  if(avl_node_balance_factor((*node)->right) < 0) { // right-right
    avl_rotate_left(node);
    return;
  }
  avl_rotate_rl(node); // right-left
}

void avl_balance_tree(Node** root) {
  if(*root == NULL) return;
  avl_balance_tree(&(*root)->right);
  avl_balance_tree(&(*root)->left);
  avl_balance_node(root);
}

/*-------------------WRAPPER FUNCTIONS-------------------*/

void avl_insert(Node** root, int key) {
  insert(root,key);
  avl_balance_tree(root);
}

void avl_delete(Node** root, int key) {
  delete_key(root, key);
  avl_balance_tree(root);
}








