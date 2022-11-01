#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
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

Stack* init(int capacity) {
  if(capacity == 0) {
    printf("Capacity cannot be lower or equal to zero");
    return NULL;
  }
  Stack* new_stack = (Stack*)malloc(sizeof(Stack));
  new_stack->arr = (int*)malloc(sizeof(int) * capacity);
  new_stack->capacity = capacity;
  new_stack->top = -1;
  return new_stack;
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

int pop(Stack* stack) {
  if(is_empty(*stack)) return -1;
  int rv = stack->arr[stack->top];
  stack->top--;
  if(stack->top < stack->capacity / 4) {
    stack->capacity /= 2;
    stack->arr = (int*)realloc(stack->arr, stack->capacity * sizeof(int));
  }
  return rv;
}

int peek(Stack stack) {
  if(is_empty(stack)) return -1;
  return stack.arr[stack.top];
}

int is_full(Stack stack) {
  return stack.top == (stack.capacity - 1);
}

int is_empty(Stack stack) {
  return stack.top == -1;
}

int is_equal(Stack stack1, Stack stack2) {
  if(stack1.top != stack2.top) return 0;
  for(int i = 0; i < stack1.top; i++) {
    if(stack1.arr[i] != stack2.arr[i]) return 0;
  }
  return 1;
}

void push(Stack* stack, int data) {
  if(stack == NULL) return;
  if(is_full(*stack) == 1) {
    stack->capacity *= 2;
    stack->arr = (int*)realloc(stack->arr, stack->capacity * sizeof(int));
  }

  stack->top++;
  stack->arr[stack->top] = data;

}

void clear(Stack* stack) {
  if(stack == NULL) {
    printf("Stack passed to clear() is NULL");
    return;
  }
  free(stack->arr);
  stack->top = 0;
}

void clear_and_free(Stack* stack) {
  if(stack == NULL) {
    printf("Stack passed to clear_and_free() is NULL");
    return;
  }

  clear(stack);
  free(stack);
}

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


