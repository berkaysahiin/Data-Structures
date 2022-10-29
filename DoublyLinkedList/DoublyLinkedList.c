#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "DoublyLinkedList.h"

int main() {
  Node* tail = NULL;
  Node* head = NULL;

  doubly_linked_list_init(&tail, &head, 82);
  doubly_linked_list_insert_end(&head, 222);
  doubly_linked_list_insert_end(&head, 333);
  doubly_linked_list_insert_end(&head, 444);

  doubly_linked_list_remove_node(&tail, &head, tail);

  doubly_linked_list_print_tail(tail);
  printf("----------------------------\n");
  doubly_linked_list_print_head(head);

  doubly_linked_list_deallocate(&tail, &head);
}
// -------------------------------------------------------------------------------------------------------------------------------------------------------

void doubly_linked_list_print_tail(Node* tail) {
  for(Node* curr = tail; curr != NULL; curr = curr->next) {
    printf(":::%d:::\n", curr->value);
  }
}

void doubly_linked_list_print_head(Node* head) {
  for(Node* curr = head; curr != NULL; curr = curr->prev) {
    printf(":::%d:::\n", curr->value);
  }
}

void doubly_linked_list_init(Node** tail, Node** head, int value) {
  Node* new_node = malloc(sizeof(Node));
  if(new_node == NULL) exit(2);
  new_node->value = value;
  new_node->prev = NULL;
  new_node->next = NULL;

  *tail = new_node;
  *head = new_node;
}

void doubly_linked_list_insert_end(Node** head, int value) {
  Node* new_node = malloc(sizeof(Node));
  if(new_node == NULL) exit(3);
  new_node->value = value;
  new_node->next = NULL;
  new_node->prev = *head;
  (*head)->next = new_node;
  *head = new_node;
}

void doubly_linked_list_insert_after(Node** node, int value) {
  Node* new_node = malloc(sizeof(Node));
  if(new_node == NULL) exit(4);
  new_node->value = value;
  new_node->prev = (*node);
  new_node->next = (*node)->next;

  if((*node)->next != NULL) {
    (*node)->next->prev = new_node;
    (*node)->next = new_node;
  }
  else {
    (*node)->next = new_node;
    (*node) = new_node; 
  }
}

void doubly_linked_list_insert_beginnig(Node** tail, int value) {
  Node* new_node = malloc(sizeof(Node));
  if(new_node == NULL) return;
  new_node->value = value;
  new_node->prev = NULL;
  new_node->next = *tail;
 (*tail)->prev = new_node;
  *tail = new_node;
}

void doubly_linked_list_remove_node(Node** tail, Node** head, Node* node) {
  if(node == NULL) return;
  if(node->prev == NULL) {
    node->next->prev = NULL;
    Node* node_next = node->next; 
    free(node);
    *tail = node_next;
    return;
  }
  if(node->next == NULL) {
    Node* node_prev = node->prev;
    node->prev->next = NULL;
    free(node);
    *head = node_prev;
    return;
  }
  
  printf("test");
  node->next->prev = node->prev;
  node->prev->next = node->next;
  free(node);
  
}

Node* doubly_linked_list_find_node(Node* tail, int value) {
  for(Node* curr = tail; curr != NULL; curr = curr->next) {
    if(curr->value == value) {
      return curr;
    }
  }
  return NULL;
}

Node* doubly_linked_list_find_node_recursive(Node* tail, int value) {
  if(tail == NULL) return NULL;
  if(tail->value == value) return tail;
  return doubly_linked_list_find_node_recursive(tail->next, value);
}

void doubly_linked_list_deallocate(Node** tail, Node** head) {
  if(*tail == NULL) return;
  Node* curr = *tail;  
  while(curr->next != NULL) {
    curr = curr->next;
    free(curr->prev);
  }
  free(curr);
  *tail = NULL;
  *head = NULL;
}

void doubly_linked_list_reverse(Node** tail, Node** head) {
  Node* curr = *tail;
  while(curr != NULL) {
    Node* next = curr->next;
    curr->next = curr->prev;
    curr->prev = next;

    curr = next;
  }

  Node* aux = *tail;
  *tail = *head;
  *head = aux;
}