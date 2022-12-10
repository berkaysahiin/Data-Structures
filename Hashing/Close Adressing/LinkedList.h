typedef struct Node {
  int value;
  struct Node* next;
}Node;

Node* init(int value);
Node* linked_list_get_last_node(Node** root);
Node* linked_list_find_key(Node* root, int key);
int linked_list_has_loop(Node* root);
int linked_list_length(Node* root);
int linked_list_length_recursive(Node* root);
void linked_list_print(Node* root);
void linked_list_insert_start(Node** root, int value);
void linked_list_insert_end(Node** root, int value);
void linked_list_insert_after(Node* target_node, int value);
void linked_list_remove_node(Node** target_node);
void linked_list_remove_element(Node** root, int value);
void linked_list_deallocate(Node** root);
void linked_list_deallocate_recursive(Node** root);
void linked_list_reverse(Node** root);
