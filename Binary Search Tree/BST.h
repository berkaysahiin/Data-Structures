#ifndef BST_REIMPLEMENTED_BST_H
#define BST_REIMPLEMENTED_BST_H

struct Node {
    int key;
    struct Node* right;
    struct Node* left;
};
typedef struct Node Node;

Node* init(int key);

void print_tree(Node* root, int space);
void traversal_infix_left(Node* root);
void insert(Node** root, int key);
void delete_key(Node** root, int key);
void delete_tree(Node** root);
void fill_in_array(Node* root, int* array, int* startIndex, int arraySize);
void mirror(Node** root);
void joint_ascending_order(Node** base, Node* other);
void joint_descending_order(Node** base, Node* other);

int get_max(Node* root);
int get_min(Node* root);
int get_height(Node* root);
int get_element_count(Node* root);
int get_child_count(Node* node);

int is_height_balanced(Node* root);
int is_element(Node* root, int key);
int is_leaf(Node* node);
int is_equal(Node* root1, Node* root2);
int is_subtree(Node* root, Node* subtree);
int is_proper_subtree(Node* root, Node* subtree);
int is_supertree(Node* supertree, Node* root);
int is_proper_supertree(Node* supertree, Node* root);
int is_full(Node* root); // each node has 0 or 2 children
int is_complete(Node* root); // each level is filled, except the last level, which is filled from left to right
int is_perfect(Node* root); // all leaves are at the same level
int is_degenerate(Node* root); // each node has 0 or 1 children


#endif //BST_REIMPLEMENTED_BST_H
