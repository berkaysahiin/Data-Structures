#ifndef UNTITLED_B_TREE_H
#define UNTITLED_B_TREE_H

/* Some properties of B-tree:
  * 1. Every node has at most order - 1 keys.
  * 2. Every non-leaf node (except root) has at least (order / 2) keys.
  * 3. All leaves are at the same level.
  * 4. A non-leaf node with k keys has k+1 children.
  * 5. All keys of a node are sorted in increasing order.
  * 6. B-tree grows and shrinks from the root which is unlike Binary Search Tree.
  * 7. Like other balanced Binary Search Trees, time complexity to search, insert and delete is O(Logn)
  * 8. Insertion only needs to be done at leaf nodes.
*/

typedef struct b_tree b_tree;
typedef struct node node;

struct b_tree {
    struct node *root;
    int order; // order is the number of children a node can have
};

struct node {
    int* keys; // array of keys
    struct node* children; // array of children
    struct node* parent;
    int num_keys;
    int num_children;
};

int b_tree_min_key_number(int order);
int b_tree_max_key_number(int order);
int b_tree_min_child_number(int order);
int b_tree_max_child_number(int order);
int b_tree_is_leaf(node* node);

b_tree* b_tree_init(int order); // creates b-tree with given order
node* b_tree_create_node(int order); // creates node with given order

void b_tree_print_node(node* node);
void b_tree_print_tree(node* root, int space); // prints b-tree in order

void b_tree_insert(b_tree* tree, int key); // inserts key into b-tree
void b_tree_split_node(b_tree* tree, node* node); // splits node into two nodes
void b_tree_rebalance_node(b_tree *tree, node *node); // rebalances node

node* b_tree_search(b_tree* tree, int key); // searches for key in b-tree
node* b_tree_get_left_sibling(node*);
node* b_tree_get_right_sibling(node*);

int b_tree_inorder_predecessor(node* node, int key);
int b_tree_inorder_successor(node* node, int key);

void b_tree_delete_from_leaf_node(b_tree *tree, node *node, int key);
void b_tree_delete_from_root_node(b_tree*, node*, int);
void b_tree_delete_from_internal_node(b_tree*, node*, int);

void b_tree_delete_key(b_tree* tree, int key); // deletes key from b-tree

void bubble_sort(int* array, int size); // sorts array in ascending order

#endif //UNTITLED_B_TREE_H
