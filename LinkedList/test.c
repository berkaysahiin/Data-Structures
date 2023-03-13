#include "LinkedList.h"
#include <stdlib.h>
#include <stdio.h>

Node* linked_list_init(int node_count);
void test_int(int, int);

int main() {
  Node* root = linked_list_init(5);

  test_int(linked_list_length(root), 5);
  test_int(linked_list_length_recursive(root), 5);

  linked_list_insert_end(&root, -10);
  linked_list_insert_end(&root, -20);
  linked_list_insert_end(&root, -30);

  linked_list_insert_start(&root, -50);
  linked_list_insert_start(&root, -100);
  linked_list_insert_start(&root, -400);
  linked_list_find_and_insert_after(root, -50, -111);

  linked_list_remove_node(&root, -400);

  printf("last node value -> %d\n", 
      linked_list_get_last_node(root)->value);

  printf("find node has value -50 -> %d\n", 
      linked_list_find_node(root, -50)->value);

  linked_list_print(root);

  linked_list_deallocate_recursive(&root);

  linked_list_print(root);

  /* to check if program crashes with null cases */

  Node* null_root = NULL;

  test_int(linked_list_length(null_root), 0);
  test_int(linked_list_length_recursive(null_root), 0);
  linked_list_length(null_root);
  linked_list_get_last_node(null_root);
  linked_list_find_node(null_root, 0);
  linked_list_insert_start(&null_root, 0);
  linked_list_insert_after(null_root, 0);
  linked_list_insert_end(&null_root, 0);
  linked_list_reverse(&null_root);
  linked_list_has_loop(null_root);
  //linked_list_remove_node(&null_root, 0);
  linked_list_find_and_insert_after(null_root, 20, 0);    
  linked_list_deallocate(&null_root);
}

Node* linked_list_init(int node_count) {
  if(node_count == 0) return NULL;

  Node* root = linked_list_new_node(24);
  for(int i = 0; i < node_count - 1; i++) {
    linked_list_insert_end(&root, (i * i * i) * 13 + 11);
  }

  return root;
}

void test_int(int expected, int output) {
  if(expected != output) {
    fprintf(stderr, "Test failed");
    exit(1);
  }
}
