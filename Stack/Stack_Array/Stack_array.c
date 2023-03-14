#include <stdio.h>
#include <stdlib.h>
#include "Stack_array.h"

int main() {
  Stack* _stack = init(32);
  push(_stack,1);
  push(_stack,2);
  push(_stack,3);
  push(_stack,4);
  push(_stack,5);
  reverse(_stack);
  print_stack(*_stack);

  clear_and_free(_stack);
} 


/*
  Initialize stack with given capacity.
  If capacity is less than or equal to zero returns NULL.
*/
Stack* init(int capacity) {
  if(capacity <= 0) {
    printf("Capacity cannot be lower or equal to zero");
    return NULL;
  }
  
  Stack* new_stack = malloc(sizeof(Stack)); // allocate struct Stack on heap.
  new_stack->arr = malloc(sizeof(int) * capacity); // allocate array on heap with given capacity of integer.
  new_stack->capacity = capacity; // set stack capacity to parameter capacity.
  new_stack->top = -1; // top is the index to last added element to the stack. if it is -1, it means stack the stack is empty.
  return new_stack;
}

/*
  Remove the element of index top and return it. If top index is -1, since it means that the stack is empty, return -1.
  Time complexity: O(1)
*/
int pop(Stack* stack) {
  if(is_empty(*stack)) return -1; // the case which the stack is empty.
  
  int return_value = stack->arr[stack->top]; // return value
  stack->top--; // move top left.
  
  /* resize stack array if necessary */
  if(stack->top < stack->capacity / 4) {
    stack->capacity /= 2;
    stack->arr = realloc(stack->arr, stack->capacity * sizeof(int));
  }
  
  return return_value;
}

/*
  Similar to pop, but peek does not remove element, so the top index stands still. 
  No resize is made since no element is removed.
  
  Time complexity: O(1)
*/
int peek(Stack stack) {
  if(is_empty(stack)) return -1;
  return stack.arr[stack.top];
}

/*
  Time complexity: O(1)
*/
int is_full(Stack stack) {
  return stack.top == (stack.capacity - 1);
}

/*
  Time complexity: O(1)
*/
int is_empty(Stack stack) {
  return stack.top == -1;
}

/*
  Compare to stack element by element.
  Does not compare the array capacity.
  
  Time complexity: O(n)
*/
int is_equal(Stack stack1, Stack stack2) {
  if(stack1.top != stack2.top) return 0; // compare sizes. if sizes are different, basically the stacks are different.
  for(int i = 0; i < stack1.top; i++) { // compare each element one by one.
    if(stack1.arr[i] != stack2.arr[i]) return 0; // case which different elements are found,
  }
  return 1;
}

/*
  Push new element to the stack. 
  Since top is the index of last added element, new element is placed at top + 1. 
  If stack is NULL, simply returns.
  If stack array capacity is full, doubles the size of stack array then push element to top + 1.
  
  Time complexity: O(1) when reallocation is not considered else O(n).
*/
void push(Stack* stack, int data) {
  if(stack == NULL) return; // case which stack is null. simply returns.
  if(is_full(*stack) == 1) { // case which stack array capacity is fulled.
    stack->capacity *= 2; // double stack array capacity.
    stack->arr = realloc(stack->arr, stack->capacity * sizeof(int)); // reallocate stack array with capacity * 2.
  }

  stack->top++; // move top to right.
  stack->arr[stack->top] = data; // push element.
}

/*
  Set top index to -1.
  Does not modify the actual array but since top index is changed to -1, initial array elements are open to reuse.
  
  Time complexity: O(1);
*/
void clear(Stack* stack) {
  if(stack == NULL) {
    printf("Stack passed to clear() is NULL");
    return;
  }
  stack->top = -1;
}

/*
  Clear() the stack and free the stack array.
  
  Time complexity: O(1)
*/
void clear_and_free(Stack* stack) {
  if(stack == NULL) {
    printf("Stack passed to clear_and_free() is NULL");
    return;
  }

  clear(stack);
  free(stack->arr);
}

/* 
  print each element of stack starting bottom to top.
*/
void print_stack(Stack stack) {
  if(is_empty(stack)) {
    printf("Stack is empty");
  }

  for(int i = 0; i < stack.top + 1; i++) {
    printf("%d ", stack.arr[i]);
  }
}

void reverse(Stack* stack) {
  if(stack == NULL) {
    printf("Error: NULL pointer passed to reverse().");
    return;
  }
  if(is_empty(*stack)) {
    printf("Stack is empty.");
    return;
  }

  int* temp = (int*)malloc(stack->capacity * sizeof(int));
  if(temp == NULL) {
    printf("Error: Memory allocation failed. NULL pointer returned.");
    return;
  }
  printf("capacity is-> %d <- ", stack->capacity);

  int i = 0;
  while(!is_empty(*stack)) {
    temp[i] = pop(stack);
    i++;
  }

  for(int j = 0; j < i; j++) {
    push(stack, temp[j]);
  }
}

Stack* clone(Stack stack) {
  if(is_empty(stack) ) {
    printf("Stack is empty. Returned NULL.");
    return NULL;
  }

  Stack* clone = init(stack.capacity);
  for(int i = 0; i < stack.top + 1; i++) {
    push(clone, stack.arr[i]);
  }
  return clone;
}
