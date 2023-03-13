struct Node {
  int value; // data stored by Node.
  struct Node* next; // pointer to next struct Node
};

typedef struct Node Node;

Node* linked_list_new_node(int value);
Node* linked_list_find_node(Node* root, int value);
Node* linked_list_get_last_node(Node* root);

int linked_list_has_loop(Node* root);
int linked_list_length(Node* root);
int linked_list_length_recursive(Node* root);

void linked_list_print(Node* root);
void linked_list_insert_start(Node** root, int value);
void linked_list_insert_end(Node** root, int value);
void linked_list_insert_after(Node* target_node, int value);
void linked_list_find_and_insert_after(Node* root, int after, int value);
void linked_list_remove_node(Node** root, int removed);
void linked_list_deallocate(Node** root);
void linked_list_deallocate_recursive(Node** root);
void linked_list_reverse(Node** root);
