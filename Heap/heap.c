#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <errno.h>

#include "heap.h"

int main() {
  int arr[10] = {19,721,17,29,31,90,66,44,22,91};
  int arr2[10] = {12,71,699,102,689,762,164,629,712};

  heap* h1 = heapify(arr, 10);
  heap* h2 = heapify(arr2, 10);

  merge(&h1, &h2);

  print_as_tree(h1);
  check(h1);
}

//---------------------------------------------------------------------------
void print_as_tree(heap* h) {
  _print_as_tree(h, 0, 40);
}

void _print_as_tree(heap* h, int index, int space) {
  space += 10;
  int right_index = get_right_child(h, index);
  if(right_index <= h->count -1) _print_as_tree(h, right_index, space);
  
  for(int i = 10; i < space; i++) {
    printf(" ");
  }

  printf("%d\n", h->arr[index]);

  int left_index = get_left_child(h, index);
  if(left_index <= h->count -1) _print_as_tree(h, left_index, space);
}

void print_as_arr(heap* h) {
  assert(h != NULL);
  for(int i = 0; i < h->count; i++) {
    printf("%d ", h->arr[i]);
  }
}

void check(heap* h) {
  for(int i = 0; i < h->count; i++) {
    if(i != 0) {
      int parent = get_parent(h, i);
      if(h->arr[parent] < h->arr[i]) {
        printf("<Test failed>(parent:%d, child:%d)\n",h->arr[parent], h->arr[i]);
        return;
      }
    }
  }
  printf("\n<Test passed>\n");
}

heap* init(int size) {
  assert(size > 0);
  heap* temp = (heap*)malloc(sizeof(heap));
  temp->count = 0;
  temp->size = size;
  temp->arr = (int*)malloc(sizeof(int) * size);
  return temp;
}

heap* heapify(int* arr, int size) { // in this implementation, it copies arr into h.arr
  assert(arr != NULL);
  assert(size >= 0);

  heap* h = init(size);
 
  for(int i = 0; i < size; i++) {
    push(&h, arr[i]);
  }
  return h;
}

void merge(heap** h1, heap** h2) { 
  while(!is_empty(*h2)) {
    push(h1, pop(h2));
  }
  free((*h2)->arr);
  free(*h2);
}


void purge(heap** h) {
  free((*h)->arr);
  free(*h);
}


int get_left_child(heap* h, int index) {
 return 2*index + 1;
}

int get_right_child(heap* h, int index) {
  return 2*index + 2;
}

int get_parent(heap* h, int index) {
  return (index - 1) / 2;
}

int push(heap** h, int key) {
  assert(h != NULL && *h != NULL);

  if((*h)->count == (*h)->size) { // array is full so reallocate 
    (*h)->size = (*h)->size * 2;
    int* new_array = calloc((*h)->size, sizeof(int));
    for(int i = 0; i < (*h)->count; i++) {
      new_array[i] = (*h)->arr[i];
    }
    free((*h)->arr);
    (*h)->arr = new_array;
    if((*h)->arr == NULL) {
      fprintf(stderr,"Reallocation of heap array is failed : %s", strerror(errno));
    }
  }
  (*h)->arr[(*h)->count] = key;
  (*h)->count++;
   sift_up(*h, (*h)->count - 1);
  return 0;
}

void sift_up(heap* h, int index) {
  assert(h != NULL);
  int parent = get_parent(h, index);
  if(parent >= 0 && h->arr[parent] < h->arr[index]) {
    // swap
    int temp = h->arr[parent];
    h->arr[parent] = h->arr[index];
    h->arr[index] = temp;
    sift_up(h, parent);
  }
}

void sift_down(heap* h, int index) {
  assert(h != NULL);

  int left_child_index = get_left_child(h,index);
  int right_child_index = get_right_child(h, index);

  // if a child's index is beyond array's bound this means that it simply doesnot exists.
  if(left_child_index > h->count -1 && right_child_index > h->count -1) return;

  int max_index;

  if(left_child_index <= h->count - 1 && right_child_index <= h->count -1) {
    max_index = h->arr[left_child_index] > h->arr[right_child_index] ? left_child_index : right_child_index;
  }
  else if(left_child_index > h->count - 1) {
    max_index = right_child_index;
  }
  else if(right_child_index > h->count -1) {
    max_index = left_child_index;
  }

  // swap 

  int key = h->arr[index];
  if(key > h->arr[max_index]) return;
  // else swap
  h->arr[index] = h->arr[max_index];
  h->arr[max_index] = key;

  sift_down(h, max_index);
}

int is_empty(heap* h) {
  return h->count == 0;
}

int get_size(heap* h) {
  return h->count;
}
int peek(heap* h) {
  return h->arr[h->count - 1];
}

int pop(heap** h) {
  if(is_empty(*h)) return -1;
  int root = (*h)->arr[0]; // return value
  (*h)->arr[0] = (*h)->arr[(*h)->count - 1]; // set root as the last element of the arr
  (*h)->arr[(*h)->count - 1] = root;
  (*h)->count--;
  sift_down(*h,0);
  return root;
}
