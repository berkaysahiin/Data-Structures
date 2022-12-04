#ifndef HEAP_HEAP_H
#define HEAP_HEAP_H

struct heap{
  int* arr;
  int size;
  int count;
};

typedef struct heap heap;

//------------------------INITIALIZE-------------------------------------------
heap* init(int size); // initialize heap with given size.
heap* heapify(int* arr, int size); // create a heap out of given array.

//---------------------------PROPERTIES------------------------------------------
int get_left_child(heap*, int);
int get_right_child(heap*, int);
int get_parent(heap*, int);
int get_size(heap*);
int is_empty(heap*);

//-------------------------PUBLIC---------------------------------------------
int peek(heap*); // get root without deleting it.
int pop(heap**); // get root and delete it.
int push(heap**, int); // push element to heap.

//------------------------PRIVATE--------------------------------------------
void sift_up(heap* h, int index);
void sift_down(heap* h, int index);

//-----------------------DEBUG-----------------------------------------------
void print_as_arr(heap*);
void print_as_tree(heap*); // wrapper.
void _print_as_tree(heap*, int, int);
void check(heap*); // check if heap is violating properties of heap tree.


#endif //HEAP_HEAP_H
