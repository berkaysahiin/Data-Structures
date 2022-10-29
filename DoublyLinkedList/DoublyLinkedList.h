typedef struct Node
{
    int value;
    struct Node* next;
    struct Node* prev;
}Node;

void doubly_linked_list_init(Node** tail, Node** head, int value);
void doubly_linked_list_print_tail(Node* tail);
void doubly_linked_list_print_head(Node* head);
void doubly_linked_list_insert_beginnig(Node** tail, int value);
void doubly_linked_list_insert_end(Node** head, int value);
void doubly_linked_list_insert_after(Node** node, int value);
void doubly_linked_list_remove_node(Node** tail, Node** head, Node* node);
void doubly_linked_list_deallocate(Node** tail, Node** head);
void doubly_linked_list_reverse(Node** tail, Node** head);
Node* doubly_linked_list_find_node(Node* tail, int value);
Node* doubly_linked_list_find_node_recursive(Node* tail, int value);
