#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "LinkedList.h"

Node* init(int _value) {
  Node* node = malloc(sizeof(Node));
  node->value = _value;
  node->next = NULL;
  return node;
}

Node* linked_list_get_last_node(Node** root) {
  Node* last_node;
  for(last_node = *root; last_node->next != NULL; last_node = last_node->next);
  return last_node;
}

Node* linked_list_find_key(Node* root, int key) {
  for(Node* curr = root; curr != NULL; curr = curr->next) {
    if(curr->value == key) {
      return curr;
    }
  }
  return NULL;
}

int linked_list_has_loop(Node* root) {
  Node* slow = root;
  Node* fast = root;

  while(fast != NULL && fast->next != NULL) {
    slow = slow->next;
    fast = fast->next->next;
    if(slow == fast) {
      printf("has loop"); 
      return 1;
    }
  }
  printf("doesnt have loop");
  return 0;
}

int linked_list_length(Node* root) {
  int count = 0;
  for(Node* curr = root; curr != NULL; curr = curr->next) {
    count++;
  }
  return count;
}

int linked_list_length_recursive(Node* root) {
  if(root == NULL) return 0;
  
  return 1 + linked_list_length_recursive(root->next);   
}

void linked_list_print(Node* root) {
  for(Node* curr = root; curr != NULL; curr = curr->next) {
    printf("%d->", curr->value);
  }
  printf(":::NULL:::");
}

void linked_list_insert_end(Node** root, int value) {
  Node* new_node = init(value);

  if(*root == NULL) {
    *root = new_node;
    return;
  }

  Node* curr;
  for(curr = *root; curr->next != NULL; curr = curr->next);
  curr->next = new_node;
}

void linked_list_insert_start(Node** root, int value) {
  Node* new_node = malloc(sizeof(Node));
  new_node->value = value;
  new_node->next = NULL;
  
  new_node->next = *root;
  *root = new_node;
}

void linked_list_insert_after(Node* target_node, int value) {
  if(target_node == NULL) exit(1);

  Node* new_node = malloc(sizeof(Node));
  new_node->value = value;
  new_node->next = target_node->next;
  target_node->next = new_node;
}

void linked_list_remove_node(Node** target_node) { // not sure which mem to free
  Node* node_after_target_node  = (*target_node)->next;
  free(*target_node);
  *target_node = node_after_target_node;
}

void linked_list_remove_element(Node** root, int value) {
  if(*root == NULL) return;

  if((*root)->value == value){
    Node* node_after_root = (*root)->next;
    free(*root);
    *root = node_after_root; 
    return;
  } 

  Node* node_before_target_node = NULL;
  for(Node* curr = *root; curr->next != NULL; curr = curr->next) {
    if(curr->next->value == value) {
       node_before_target_node = curr; 
    }
  }

  if(node_before_target_node == NULL) return;

  Node* node_after_target_node = node_before_target_node->next->next;
  free(node_before_target_node->next);
  node_before_target_node->next = node_after_target_node;
}

void linked_list_deallocate(Node** root) {
  Node* current_node;
  while(current_node != NULL) {
    Node* prev_node = current_node;
    current_node = current_node->next;
    free(prev_node);
  }
  *root = NULL;
}

void linked_list_deallocate_recursive(Node** root) {
  Node* current_node = *root;
  Node* prev_node = current_node;
  current_node = current_node->next;
  free(prev_node);

  if(current_node != NULL) {
    linked_list_deallocate_recursive(&current_node);
  }
  *root = NULL;
}

void linked_list_reverse(Node** root) {
  Node* current_node = *root;
  Node* prev_node = NULL;

  while(current_node != NULL) {
    Node* next_node = current_node->next;
    current_node->next = prev_node;
    prev_node = current_node;
    current_node = next_node;
  }
  *root = prev_node;
}
