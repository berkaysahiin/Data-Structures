#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "b-tree.h"
#include <math.h>


b_tree* b_tree_init(int order) {
  assert(order > 2);
  b_tree* tree = malloc(sizeof(b_tree));
  tree->root = NULL;
  tree->order = order;
  return tree;
}

node* b_tree_create_node(int order) {
  node* new_node = malloc(sizeof(node));
  new_node->keys = malloc(sizeof(int) * b_tree_max_key_number(order));
  new_node->children = malloc(sizeof(node) * b_tree_max_child_number(order));
  new_node->num_keys = 0;
  new_node->parent = NULL;
  return new_node;
}

node* b_tree_search(b_tree* tree, int key) {
  node* current_node = tree->root;
  while (current_node != NULL) {
    for (int i = 0; i < current_node->num_keys; i++) {
      if (current_node->keys[i] == key) {
        return current_node;
      }
    }
    for (int i = 0; i < current_node->num_keys; i++) {
      if (current_node->keys[i] > key) {
        current_node = &current_node->children[i];
        break;
      }
    }
  }
  return NULL;
}

void b_tree_insert(b_tree* tree, int key) { // insertion only needs to be done at leaf nodes
  if(tree->root == NULL) {
    tree->root = b_tree_create_node(tree->order);
    tree->root->keys[0] = key;
    tree->root->num_keys++;
    return;
  }

  node* current = tree->root;
  node* parent_of_current = NULL;
  while(!b_tree_is_leaf(current)) {
    parent_of_current = current;
    for(int i = 0; i < current->num_keys; i++) {
      if(key < current->keys[i]) {
        current = &current->children[i];
        break;
      }
      if(i == current->num_keys - 1) {
        current = &current->children[i + 1];
        break;
      }
    }
  }
  current->parent = parent_of_current;
  // current is now a leaf node and parent_of_current is its parent

  if(current->num_keys < b_tree_max_key_number(tree->order)) {
    current->keys[current->num_keys] = key;
    current->num_keys++;
    bubble_sort(current->keys, current->num_keys); // TODO: optimize this
  } else {
    // add key to the node, sort and split the node
    current->keys[current->num_keys] = key;
    current->num_keys++;
    bubble_sort(current->keys, current->num_keys);
    b_tree_split_node(tree, current);
  }
}

void b_tree_split_node(b_tree* tree, node* node) {
  int middle_index = tree->order % 2 == 0 ? tree->order / 2 : (tree->order -1) / 2;
  struct node* new_left_node = b_tree_create_node(tree->order);
  struct node* new_right_node = b_tree_create_node(tree->order);
  new_left_node->parent = node->parent;
  new_right_node->parent = node->parent;

  printf("middle index: %d, value: %d\n", middle_index, node->keys[middle_index]);

  // copy keys to new nodes
  for(int i = 0; i < middle_index; i++) {
    new_left_node->keys[i] = node->keys[i];
    new_left_node->num_keys++;
  }

  for(int i = middle_index + 1; i < node->num_keys; i++) {
    new_right_node->keys[i - middle_index - 1] = node->keys[i];
    new_right_node->num_keys++;
  }

  if(!b_tree_is_leaf(node)) { // if node is not a leaf, copy children to new nodes.
    for(int i = 0; i < middle_index + 1; i++) {
      new_left_node->children[i] = node->children[i];
      new_left_node->num_children++;
      new_left_node->children[i].parent = new_left_node;
    }
    for(int i = middle_index + 1; i < node->num_children; i++) {
      new_right_node->children[i - middle_index - 1] = node->children[i];
      new_right_node->num_children++;
      new_right_node->children[i - middle_index - 1].parent = new_right_node;
    }
  }

  if(node->parent == NULL) { // if node is root node
    node->parent = b_tree_create_node(tree->order);
    printf("<child count of root node: %d>\n", node->parent->num_children);
    node->parent->children[0] = *new_left_node;
    node->parent->children[1] = *new_right_node;
    node->parent->keys[0] = node->keys[middle_index];
    node->parent->num_keys++;
    node->parent->num_children = 2;
    tree->root = node->parent;
    tree->root->children[0].parent = tree->root;
    tree->root->children[1].parent = tree->root;
  }
  else {
    // first add middle key to parent
    node->parent->keys[node->parent->num_keys] = node->keys[middle_index];
    node->parent->num_keys++;
    bubble_sort(node->parent->keys, node->parent->num_keys);
    // new node array for parent
    struct node* new_children_left = b_tree_create_node(tree->order);
    struct node* new_children_right = b_tree_create_node(tree->order);
    // copy children to new node array
    for(int i = 0; i < middle_index; i++) {
      new_children_left->keys[i] = node->keys[i];
      new_children_left->num_keys++;
      new_children_left->parent = node->parent;
    }
    for(int i = middle_index + 1; i < node->num_keys; i++) {
      new_children_right->keys[i - middle_index - 1] = node->keys[i];
      new_children_right->num_keys++;
      new_children_right->parent = node->parent;
    }
    struct node* nodes_parent = node->parent;
    for(int i = 0; i < node->parent->num_children; i++) {
      if(node->parent->keys[i] == node->keys[middle_index]) {
        // insert left children before at i and right children after at i + 1.
        for(int j = nodes_parent->num_children; j > i; j--) {
          nodes_parent->children[j] = nodes_parent->children[j - 1];
        }
        nodes_parent->children[i] = *new_children_left;
        nodes_parent->children[i + 1] = *new_children_right;
        nodes_parent->num_children += 1;
        break;
      }
    }
  }

  // check if parent needs to be split
  if(node->parent->num_keys > b_tree_max_key_number(tree->order)) {
    b_tree_split_node(tree, node->parent);
  }
}

void b_tree_rebalance_node(b_tree *tree, node *node) {
  printf("this worked");
  assert(tree != NULL);
  assert(node != NULL);
  if (node->num_keys >= b_tree_min_key_number(tree->order)) return;

  // if not root node, try to borrow from sibling nodes else merge with sibling nodes
  if (node->parent != NULL) {
    // find index of node in parent's children array
    int index = 0;
    for (int i = 0; i < node->parent->num_children; i++) {
      if (node->parent->children[i].keys[0] == node->keys[0]) {
        index = i;
        break;
      }
    }
    // try to borrow from left sibling
    if (index > 0) {
      struct node *left_sibling = &node->parent->children[index - 1];
      if (left_sibling->num_keys > b_tree_min_key_number(tree->order)) {
        // borrow from left sibling
        node->keys[node->num_keys] = left_sibling->keys[left_sibling->num_keys - 1];
        node->num_keys++;
        bubble_sort(node->keys, node->num_keys);
        left_sibling->keys[left_sibling->num_keys - 1] = 0;
        left_sibling->num_keys--;
        return;
      }
    }
    // try to borrow from right sibling
    if (index < node->parent->num_children - 1) {
      struct node *right_sibling = &node->parent->children[index + 1];
      if (right_sibling->num_keys > b_tree_min_key_number(tree->order)) {
        // borrow from right sibling
        node->keys[node->num_keys] = right_sibling->keys[0];
        node->num_keys++;
        bubble_sort(node->keys, node->num_keys);
        right_sibling->keys[0] = 0;
        bubble_sort(right_sibling->keys, right_sibling->num_keys);
        right_sibling->num_keys--;
        return;
      }
    }

    // if no sibling can borrow, merge with sibling

    // merge with left sibling
    if (index > 0) {
      struct node *left_sibling = &node->parent->children[index - 1];
      // move all keys from node to left sibling
      for (int i = 0; i < node->num_keys; i++) {
        left_sibling->keys[left_sibling->num_keys] = node->keys[i];
        left_sibling->num_keys++;
      }
      // move all children from node to left sibling
      if (!b_tree_is_leaf(node)) {
        for (int i = 0; i < node->num_children; i++) {
          left_sibling->children[left_sibling->num_children] = node->children[i];
          left_sibling->num_children++;
        }
      }
      // remove node from parent's children array
      for (int i = index; i < node->parent->num_children - 1; i++) {
        node->parent->children[i] = node->parent->children[i + 1];
      }
      node->parent->num_children--;
      // remove key from parent's keys array
      for (int i = index - 1; i < node->parent->num_keys - 1; i++) {
        node->parent->keys[i] = node->parent->keys[i + 1];
      }
      node->parent->num_keys--;
      // check if parent needs to be rebalanced
      if (node->parent->num_keys < b_tree_min_key_number(tree->order)) {
        b_tree_rebalance_node(tree, node->parent);
      }
      return;
    }

    // merge with right sibling
    struct node *right_sibling = &node->parent->children[index + 1];

    // move all keys from node to right sibling
    for (int i = 0; i < node->num_keys; i++) {
      right_sibling->keys[right_sibling->num_keys] = node->keys[i];
      right_sibling->num_keys++;
    }

    // move all children from node to right sibling
    if (!b_tree_is_leaf(node)) {
      for (int i = 0; i < node->num_children; i++) {
        right_sibling->children[right_sibling->num_children] = node->children[i];
        right_sibling->num_children++;
      }
    }

    // remove node from parent's children array
    for (int i = index; i < node->parent->num_children - 1; i++) {
      node->parent->children[i] = node->parent->children[i + 1];
    }
    node->parent->num_children--;

    // remove key from parent's keys array
    for (int i = index; i < node->parent->num_keys - 1; i++) {
      node->parent->keys[i] = node->parent->keys[i + 1];
    }
    node->parent->num_keys--;

    // check if parent needs to be rebalanced
    if (node->parent->num_keys < b_tree_min_key_number(tree->order)) {
      b_tree_rebalance_node(tree, node->parent);
    }
    return;
  }

  // if root is empty, make first child the new root
  if (node->num_keys == 0) {
    // if root has no keys, make first child the new root
    tree->root = &node->children[0];
    tree->root->parent = NULL;
  }
}

void b_tree_print_node(node* root) {
  assert(root != NULL);
  for(int i = 0; i < root->num_keys; i++) {
    printf("%d ", root->keys[i]);
  }
}

void b_tree_print_tree(node* root, int space) {
  assert(root != NULL);

  for(int i = 0; i < space; i++) {
    printf(" ");
  }

  b_tree_print_node(root);

  if(b_tree_is_leaf(root)) return;
  int child_num = root->num_children;
  int f = floor(child_num / 2);
  printf("\n");
  for(int i = 0; i < f; i++) {
    b_tree_print_tree(&root->children[i], space - 5);
  }
  for(int i = f ; i < child_num; i++) {
    b_tree_print_tree(&root->children[i], 5);
  }
}

void b_tree_delete_key(b_tree* tree, int key) {
//  /* cases:
//   1. key is in leaf node and has enough keys: delete key
//   2. key is in leaf node and has not enough keys.
//      a. if one of the siblings has enough keys, borrow a key from sibling.
//      b. if both siblings have not enough keys, merge with sibling.
//      c. if parent node has only one key, merge with sibling. this merging through parent node.
//  3. key is in internal node and has enough keys: delete key
//  4. key is in internal node and has not enough keys.
//      a. if one of the siblings has enough keys, borrow a key from sibling.
//      b. if both siblings have not enough keys, merge with sibling.
//      c. if parent node has only one key, merge with sibling. this merging through parent node.
//  5. key is in root node and has enough keys: delete key
//  6. key is in root node and has not enough keys.
//      a. if one of the siblings has enough keys, borrow a key from sibling.
//      b. if both siblings have not enough keys, merge with sibling.
//      c. if parent node has only one key, merge with sibling. this merging through parent node.
//  */
  node* target_node = b_tree_search(tree, key);
  if(target_node == NULL) return;

  if(b_tree_is_leaf(target_node)) {
    b_tree_delete_from_leaf_node(tree, target_node, key);
    return;
  }

  b_tree_delete_from_internal_node(tree, target_node, key);

}

void b_tree_delete_from_leaf_node(b_tree* tree, node* node, int key) {
  assert(node != NULL);
  assert(b_tree_is_leaf(node));
  assert(node->parent != NULL);
  // if node has enough keys to delete key, delete key
  if (node->num_keys > b_tree_min_key_number(tree->order)) {
    for (int i = 0; i < node->num_keys; i++) {
      if (node->keys[i] == key) {
        for (int j = i; j < node->num_keys - 1; j++) {
          node->keys[j] = node->keys[j + 1];
        }
        node->num_keys--;
        break;
      }
    }
    return; // done
  }

  // if node has not enough keys to delete key, borrow or merge.

  // if left or right sibling has enough keys, borrow key from sibling.
  struct node *left_sibling = b_tree_get_left_sibling(node);
  struct node *right_sibling = b_tree_get_right_sibling(node);

  if (right_sibling != NULL && right_sibling->num_keys > b_tree_min_key_number(tree->order)) {
    // delete key from node
    for (int i = 0; i < node->num_keys; i++) {
      if (node->keys[i] == key) {
        for (int j = i; j < node->num_keys - 1; j++) {
          node->keys[j] = node->keys[j + 1];
        }
        node->num_keys--;
        break;
      }
    }

    // get left-most key from right sibling
    int left_most_key = right_sibling->keys[0];
    // delete left-most key from right sibling
    for (int i = 0; i < right_sibling->num_keys - 1; i++) {
      right_sibling->keys[i] = right_sibling->keys[i + 1];
    }
    right_sibling->num_keys--;

    // get index of node in parents children
    int index = 0;
    for (int i = 0; i < node->parent->num_children; i++) {
      if (node->parent->children[i].keys[0] == node->keys[0]) {
        index = i;
        break;
      }
    }
    // insert parent's key at index to node
    node->keys[node->num_keys] = node->parent->keys[index];
    node->num_keys++;
    bubble_sort(node->keys, node->num_keys);

    // delete parent's key at index
    for (int i = index; i < node->parent->num_keys - 1; i++) {
      node->parent->keys[i] = node->parent->keys[i + 1];
    }

    // insert left most key from right sibling to parent's key at index
    node->parent->keys[index] = left_most_key;
    bubble_sort(node->parent->keys, node->parent->num_keys);

    return;
  }

  if (left_sibling != NULL && left_sibling->num_keys > b_tree_min_key_number(tree->order)) {
    // delete key from node
    for (int i = 0; i < node->num_keys; i++) {
      if (node->keys[i] == key) {
        for (int j = i; j < node->num_keys - 1; j++) {
          node->keys[j] = node->keys[j + 1];
        }
        node->num_keys--;
        break;
      }
    }

    // get right-most key from left sibling
    int right_most_key = left_sibling->keys[left_sibling->num_keys - 1];
    // delete right-most key from left sibling
    left_sibling->num_keys--;

    // get index of node in parents children
    int index = 0;
    for (int i = 0; i < node->parent->num_children; i++) {
      if (node->parent->children[i].keys[0] == node->keys[0]) {
        index = i;
        break;
      }
    }
    // insert parent's key at index to node
    node->keys[node->num_keys] = node->parent->keys[index];
    node->num_keys++;
    bubble_sort(node->keys, node->num_keys);

    // delete parent's key at index
    for (int i = index; i < node->parent->num_keys - 1; i++) {
      node->parent->keys[i] = node->parent->keys[i + 1];
    }

    // insert right most key from left sibling to parent's key at index
    node->parent->keys[index] = right_most_key;
    bubble_sort(node->parent->keys, node->parent->num_keys);

    return;
  }

  // if both siblings have not enough keys merge with right sibling or left sibling. (merge with right sibling first)
  // the key between node and sibling is deleted from parent node and inserted to merged node.

  // merge with right sibling
  if (right_sibling != NULL) {

    // delete key from node
    for (int i = 0; i < node->num_keys; i++) {
      if (node->keys[i] == key) {
        for (int j = i; j < node->num_keys - 1; j++) {
          node->keys[j] = node->keys[j + 1];
        }
        node->num_keys--;
        break;
      }
    }

    // get index of node in parents children
    int index = 0;
    for (int i = 0; i < node->parent->num_children; i++) {
      if (node->parent->children[i].keys[0] == node->keys[0]) {
        index = i;
        break;
      }
    }

    // insert parent's key at index to node
    node->keys[node->num_keys] = node->parent->keys[index];
    node->num_keys++;
    bubble_sort(node->keys, node->num_keys);

    // delete parent's key at index
    for (int i = index; i < node->parent->num_keys; i++) {
      node->parent->keys[i] = node->parent->keys[i + 1];
      node->parent->num_keys--;
    }

    // insert keys from right sibling to node
    for (int i = 0; i < right_sibling->num_keys; i++) {
      node->keys[node->num_keys] = right_sibling->keys[i];
      node->num_keys++;
    }

    // adjust parents children
    node->parent->children[index] = *node;

    // delete right sibling and shift parents after right sibling left by one
    for (int i = index + 1; i < node->parent->num_children - 1; i++) {
      node->parent->children[i] = node->parent->children[i + 1];
    }
    node->parent->num_children--;
    return;
  }

  // merge with left sibling
  if (left_sibling != NULL) {

    // delete key from node
    for (int i = 0; i < node->num_keys; i++) {
      if (node->keys[i] == key) {
        for (int j = i; j < node->num_keys - 1; j++) {
          node->keys[j] = node->keys[j + 1];
        }
        node->num_keys--;
        break;
      }
    }

    // get index of node in parents children
    int index = 0;
    for (int i = 0; i < node->parent->num_children; i++) {
      if (node->parent->children[i].keys[0] == node->keys[0]) {
        index = i;
        break;
      }
    }

    // insert parent's key at index to node
    node->keys[node->num_keys] = node->parent->keys[index - 1];
    node->num_keys++;
    bubble_sort(node->keys, node->num_keys);

    // delete parent's key at index
    for (int i = index - 1; i < node->parent->num_keys - 1; i++) {
      node->parent->keys[i] = node->parent->keys[i + 1];
      node->parent->num_keys--;
    }

    // insert keys from left sibling to node
    for (int i = 0; i < left_sibling->num_keys; i++) {
      node->keys[node->num_keys] = left_sibling->keys[i];
      node->num_keys++;
    }
    bubble_sort(node->keys, node->num_keys);

    // adjust parents children
    node->parent->children[index - 1] = *node;

    // delete left sibling and shift parents after left sibling left by one
    for (int i = index; i < node->parent->num_children - 1; i++) {
      node->parent->children[i] = node->parent->children[i + 1];
    }
    node->parent->num_children--;
    return;
  }

}

void b_tree_delete_from_internal_node(b_tree *tree, node *node, int key) {
  printf("this worked");
  // delete key from node
  for (int i = 0; i < node->num_keys; i++) {
    if (node->keys[i] == key) {
      for (int j = i; j < node->num_keys - 1; j++) {
        node->keys[j] = node->keys[j + 1];
      }
      node->num_keys--;
      break;
    }
  }

  // get index of node in parents children
  int index = 0;
  for (int i = 0; i < node->parent->num_children; i++) {
    if (node->parent->children[i].keys[0] == node->keys[0]) {
      index = i;
      break;
    }
  }



}

void b_tree_delete_from_root_node(b_tree *tree, node *node, int key) {
  assert(tree != NULL);
  assert(node != NULL);
  assert(node->parent == NULL);

  // delete key from node
  for (int i = 0; i < node->num_keys; i++) {
    if (node->keys[i] == key) {
      for (int j = i; j < node->num_keys - 1; j++) {
        node->keys[j] = node->keys[j + 1];
      }
      node->num_keys--;
      break;
    }
  }
}

node* b_tree_get_left_sibling(node* node) {
  assert(node != NULL && node->parent != NULL);
  for(int i = 0; i < node->parent->num_children; i++) {
    if(node->parent->children[i].keys[0] == node->keys[0]) {
      if(i == 0) return NULL;
      return &node->parent->children[i - 1];
    }
  }
  return NULL;
}

node* b_tree_get_right_sibling(node* node) {
  assert(node != NULL && node->parent != NULL);
  for(int i = 0; i < node->parent->num_children; i++) {
    if(node->parent->children[i].keys[0] == node->keys[0]) {
      if(i == node->parent->num_children - 1) return NULL;
      return &node->parent->children[i + 1];
    }
  }
  return NULL;
}

// -----------------PROPERTIES-----------------

int b_tree_inorder_successor(node* node, int key) {
  if(node == NULL) return -1;
  if(b_tree_is_leaf(node)) {
    for(int i = 0; i < node->num_keys; i++) {
      if(node->keys[i] == key) {
        if(i == node->num_keys - 1) return -1;
        return node->keys[i + 1];
      }
    }
  }

  for(int i = 0; i < node->num_keys; i++) {
    if(node->keys[i] == key) {
      if(i == node->num_keys - 1) {
        return b_tree_inorder_successor(&node->children[i + 1], node->children[i + 1].keys[0]);
      }
      return node->keys[i + 1];
    }
  }
  return -1;
}

int b_tree_inorder_predecessor(node* node, int key) {
  if(node == NULL) return -1;
  if(b_tree_is_leaf(node)) {
    for(int i = 0; i < node->num_keys; i++) {
      if(node->keys[i] == key) {
        if(i == 0) return -1;
        return node->keys[i - 1];
      }
    }
  }

  for(int i = 0; i < node->num_keys; i++) {
    if(node->keys[i] == key) {
      if(i == 0) {
        return b_tree_inorder_predecessor(&node->children[i], node->children[i].keys[node->children[i].num_keys - 1]);
      }
      return node->keys[i - 1];
    }
  }
  return -1;
}

int b_tree_is_leaf(node* node) {
  assert(node != NULL);
  return node->num_children == 0;
}

int b_tree_min_key_number(int order) {
  return 2;
}

int b_tree_max_key_number(int order) {
  return order - 1;
}

int b_tree_min_child_number(int order) {
  return 3; // order is 5
}

int b_tree_max_child_number(int order) {
  return order;
}

// -----------------HELPER-FUNCTIONS-----------------

void bubble_sort(int* arr, int size) {
  for(int i = 0; i < size; i++) {
    for(int j = 0; j < size - i - 1; j++) {
      if(arr[j] > arr[j + 1]) {
        int temp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = temp;
      }
    }
  }
}


