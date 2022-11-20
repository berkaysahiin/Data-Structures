#pragma clang diagnostic push
#pragma ide diagnostic ignored "ArgumentSelectionDefects"
#include <stdio.h>
#include <stdlib.h>
#include "BST.h"
/*----------------------------------------------------------------------------------------------------------------------*/

Node* init(int key) {
  Node* temp = malloc(sizeof(Node));
  temp->key = key;
  temp->right = NULL;
  temp->left = NULL;
  return temp;
}

void print_tree(Node* root, int space) {
    if (root == NULL) {
      return;
    }
    space += 10;
    print_tree(root->right, space);
    printf("\n");
    for (int i = 10; i < space; i++) {
      printf(" ");
    }
    printf("%d\n", root->key);
    print_tree(root->left, space);
  }

void traversal_infix_left(Node* root) {
  if(root == NULL) return;
  traversal_infix_left(root->left);
  printf("%d ", root->key);
  traversal_infix_left(root->right);
}

void insert(Node** root, int key) {
  if(*root == NULL) {
    *root = init(key);
    return;
  }
  if((*root)->key == key) return;
  if(key > (*root)->key) return insert(&(*root)->right, key);
  return insert(&(*root)->left, key);
}

void delete_key(Node** root, int key) {
  if(*root == NULL) return;

  if((*root)->key == key) {
    if((*root)->left == NULL && (*root)->right == NULL) {
      free(*root);
      *root = NULL;
      return;
    }

    if((*root)->right != NULL) {
      int min = get_min((*root)->right);
      (*root)->key = min;
      delete_key(&(*root)->right, min);
      return;
    }

    int max = get_max((*root)->left);
    (*root)->key = max;
    delete_key(&(*root)->left, max);
    return;
  }

  if(key > (*root)->key) return delete_key(&(*root)->right, key);

  return delete_key(&(*root)->left, key);
}

void delete_tree(Node** root) {
  if(*root == NULL) return;
  delete_tree(&(*root)->right);
  delete_tree(&(*root)->left);
  free(*root);
  *root = NULL;
}

void fill_in_array(Node* root, int* array, int* startIndex, int arraySize) {
  if(root == NULL) return;
  fill_in_array(root->left, array, startIndex, arraySize);
  array[*startIndex] = root->key;
  (*startIndex)++;
  fill_in_array(root->right, array, startIndex, arraySize);
}

void mirror(Node** root) {
  if(*root == NULL) return;

  Node* temp = (*root)->left;
  (*root)->left = (*root)->right;
  (*root)->right = temp;
  mirror(&(*root)->right);
  mirror(&(*root)->left);
}

/*----------------------------------------------------------------------------------------------------------------------*/
int is_height_balanced(Node* root) {
  if(root == NULL) return -1;
  int right_height = get_height(root->right);
  int left_height = get_height(root->left);

  return abs(left_height - right_height) <= 1 && is_height_balanced(root->right) && is_height_balanced(root->left);
}

int is_element(Node* root, int key) {
  if(root == NULL)     return 0;
  if(root->key == key) return 1;
  if(key > root->key)  return is_element(root->right, key);
                       return is_element(root->left, key);
}

int is_leaf(Node* node) {
  if(node == NULL) return -1;
  return node->right == NULL && node->left == NULL;
}

int is_equal(Node* root1, Node* root2) {
  if(root1 == NULL && root2 == NULL) return 1;
  if(root1 == NULL || root2 == NULL) return 0;
  if(root1->key != root2->key)       return 0;
  return is_equal(root1->right, root2->right) && is_equal(root1->left, root2->left);
}

int is_subtree(Node* root, Node* subtree) {
  if(root == NULL && subtree == NULL) return 1;
  if(root == NULL) return 0;
  if(subtree == NULL) return 1;
  if(is_equal(root, subtree)) {
    return 1;
  }
  return is_subtree(root->right, subtree) || is_subtree(root->left, subtree);
}

int is_proper_subtree(Node* root, Node* subtree) {
  return is_subtree(root, subtree) && !is_equal(root,subtree);
}

int is_supertree(Node* supertree, Node* root) {
  return is_subtree(supertree, root);
}

int is_proper_supertree(Node* supertree, Node* root) {
  return is_supertree(supertree, root) && !is_equal(supertree,root);
}

int is_full(Node* root) {
  if(root == NULL) return 1;
  if(is_leaf(root)) return 1;
  if(root->left == NULL || root->right == NULL) return 0;
  return is_full(root->left) && is_full(root->right);
}

int is_complete(Node* root) {
  if(root == NULL) return 1;
  if(is_leaf(root)) return 1;
  if(root->left == NULL) return 0;
  if(root->right == NULL) return is_complete(root->left);
  return is_complete(root->left) && is_complete(root->right);
}

int is_degenerate(Node* root) {
  if(root == NULL) return 0;
  if(is_leaf(root)) return 1;
  if(root->left != NULL && root->right != NULL) return 0;
  if(root->left != NULL) return is_degenerate(root->left);
  return is_degenerate(root->right);
}

/*----------------------------------------------------------------------------------------------------------------------*/
int get_height(Node* root) {
  if(root == NULL) {
    return 0;
  }
  if(is_leaf(root)) return 1;
  int right_height = get_height(root->right);
  int left_height = get_height(root->left);

  return 1 + (left_height > right_height ? left_height : right_height);

}

int get_max(Node* root) {
  if(root == NULL) {
   return -1;
  }

  if(root->right != NULL) {
    return get_max(root->right);
  }

  return root->key;
}

int get_min(Node* root) {
  if(root == NULL) {
    return -1;
  }

  if(root->left != NULL) {
    return get_min(root->left);
  }

  return root->key;
}

int get_element_count(Node* root) {
  if(root == NULL) return 0;
  return 1 + get_element_count(root->right) + get_element_count(root->left);
}

int get_child_count(Node* root) {
  if(root == NULL) return 0;
  printf( "child count :%d\n", (root->right == NULL) + (root->left == NULL));
  return (root->right == NULL) + (root->left == NULL);
}

#pragma clang diagnostic pop