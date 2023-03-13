#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"

void linked_list_print(Node* root) {
  Node* iter = root; // iterator
  while(iter != NULL) { 
    printf("%d -> ", iter->value); 
    iter = iter->next;
  }
  printf(":::NULL:::");
}

int linked_list_length(Node* root) {
  Node* iter = root;
  int count = 0;

  while(iter != NULL) {
    iter = iter->next;
    count++;
  }

  return count;
}

Node* linked_list_get_last_node(Node* root) {
  if(root == NULL) return NULL;

  Node* last_node = root;
  while(last_node->next != NULL) {
    last_node = last_node->next;
  }

  return last_node;
}

Node* linked_list_find_node(Node* root, int value) {
  Node* iter = root;
  while(iter != NULL) {
    if(iter->value == value) return iter;
    iter = iter->next;
  }
  return NULL;
}

Node* linked_list_new_node(int value) {
  Node* new_node = malloc(sizeof(Node));
  new_node->value = value;
  new_node->next = NULL;
  return new_node;
}

int linked_list_length_recursive(Node* root) {
  if(root == NULL) return 0; // base case 
  
  return 1 + linked_list_length_recursive(root->next);   
}


void linked_list_insert_end(Node** root, int value) {
  Node* new_node = linked_list_new_node(value);

  if(*root == NULL) {
    *root = new_node;
    return;
  }

  linked_list_get_last_node(*root)->next = new_node;
}

void linked_list_insert_start(Node** root, int value) {
  Node* new_node = linked_list_new_node(value);
  new_node->next = *root;
  *root = new_node;
}

/* if root fails */
void linked_list_insert_after(Node* target_node, int value) {
  if(target_node == NULL) {
    fprintf(stderr, "Target node is null, aborted");
    return;
  }

  Node* new_node = linked_list_new_node(value);
  new_node->next = target_node->next;
  target_node->next = new_node;
}

void linked_list_find_and_insert_after(Node* root, int after, int value) {
  Node* find = linked_list_find_node(root, after);
  if(find == NULL) return;
  linked_list_insert_after(find, value);
}

void linked_list_remove_node(Node** root, int removed) { 
  if(*root == NULL) {
    return;
  }

  if((*root)->value == removed) {
    Node* temp = *root;
    *root = (*root)->next;
    free(temp);
    return;
  }

  Node* prev = *root;
  Node* curr = (*root)->next;

  while(curr != NULL) {
    if(curr->value == removed) {
      prev->next = curr->next;
      free(curr);
      return;
    }
    prev = curr;
    curr = curr->next;
  }
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

int linked_list_has_loop(Node* root) {
  Node* slow = root;
  Node* fast = root;

  while(fast != NULL && fast->next != NULL) {
    slow = slow->next;
    fast = fast->next->next;
    if(slow == fast) return 1;
  }

  return 0;
}
