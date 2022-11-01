#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#define __STDC_WANT_LIB_EXT1__ 1
#include <string.h>
#include "Stack_linked_list.h" // 

int main() {
  Stack* stack = init();
  push(stack, 20);
  push(stack, 30);
  push(stack, 40);
  push(stack, 50);
  Stack* cloned_stack = init();

  memberwise_copy(cloned_stack, *stack);

  print_stack(cloned_stack);

  free_stack(cloned_stack);
  free_stack(stack);
}

Stack* init(void) {
  Stack* new_stack = (Stack*)malloc(sizeof(Stack));
  if(new_stack == NULL) {
    printf("Stack memory allocation failed at init()");
    exit(1);
  }  
  new_stack->top = NULL;
  return new_stack;
}

void print_stack(Stack* stack) {
  if(stack == NULL) {
    printf("given stack to print() is NULL");
    exit(2);
  }
  for(Node* curr = stack->top; curr != NULL; curr = curr->next) {
    printf("%d ", curr->data);
  }
}

void push(Stack* stack, int data) {
  Node* new_node = (Node*)malloc(sizeof(Node));
  if(new_node == NULL) exit(2);
  new_node->data = data;
  new_node->next = stack->top;
  stack->top = new_node;
}

int pop(Stack* stack) {
  if(stack == NULL) {
    printf("given stack to pop() is NULL");
    exit(3);
  }
  if(stack->top == NULL) {
    printf("Stack is empty. pop() failed");
    return -1;
  }
  Node* pop_node = stack->top;
  int return_data = pop_node->data;
  stack->top = stack->top->next;
  free(pop_node);
  return return_data;
}

int peek(Stack* stack) {
  if(stack == NULL) {
    printf("Stack given to peek() is NULL");
    exit(4);
  }

  if(stack->top == NULL) {
    printf("Stack is empty. peek() failed");
    return -1;
  }

  return stack->top->data;
}

int is_empty(Stack* stack) {
  return stack->top == NULL;
}

void clear(Stack* stack) {
  if(stack == NULL) {
    printf("Given stack to clear() is NULL");
    exit(4);
  }

  Node* curr = stack->top;
  while(curr != NULL) {
    Node* temp = curr;
    curr = curr->next;
    free(temp);
  }
  stack->top = NULL;
}

void free_stack(Stack* stack) {
  clear(stack);
  free(stack);
}

void memberwise_copy(Stack* dest, Stack source) { 
  if(dest == NULL) {
    printf("Given stack to memberwise_clone() is NULL");
    exit(5);
  }
  clear(dest);
  Node* curr = source.top;
  while(curr != NULL) {
    push(dest, curr->data);
    curr = curr->next;
  }
  reverse(dest);
} 

void reverse(Stack* stack) { // reverse given stack
  if(stack == NULL) {
    printf("Stack given to reverse() is NULL");
    exit(5);
  }

  if(stack->top == NULL) return;

  Stack* temp_stack = init();
  while(!is_empty(stack)) {
    push(temp_stack, pop(stack));
  }

  Node* tail = NULL;
  Node* iter = temp_stack->top;

  while(iter != NULL) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = iter->data;
    new_node->next = NULL;

    if(stack->top == NULL) {
      stack->top = new_node;
      tail = new_node;
    }
    else {
      tail->next = new_node;
      tail = tail->next;
    }
    
    iter = iter->next;
  } 
 
  free_stack(temp_stack);
}

int equal(Stack* stack1, Stack* stack2) {
  if(stack1 == NULL || stack2 == NULL) {
    printf("ERROR: NULL Stack passed to equal()");
    exit(6);
  }

  Node* curr_1 = stack1->top;
  Node* curr_2 = stack2->top;
  
  while(curr_1 != NULL && curr_2 != NULL) {
    if(curr_1->data != curr_2->data) {
      return 0;
    }
    curr_1 = curr_1->next;
    curr_2 = curr_2->next; 
  }

  if(curr_1 == NULL && curr_1 == NULL) return 1;
  else return 0;
}

int contains(Stack* stack, int data) {
  if(stack == NULL) {
    printf("ERROR: Stack passed to contains is NULL");
    exit(7);
  }

  for(Node* curr = stack->top; curr != NULL; curr = curr->next) {
    if(curr->data == data) {
      return 1;
    }
  }
  return 0;
}

int get_size(Stack* stack) {
  int i = 0;
  for(Node* curr = stack->top; curr != NULL; curr = curr->next) {
    i++;
  }
  return i;
}

int* to_array(Stack* stack) {
  if(stack == NULL) {
    printf("ERROR: Stack passed to to_array() is NULL");
    exit(7);
  }
  if(stack->top == NULL) {
    printf("Warning: Stack passed to to_array() is empty. returned NULL");
    return NULL;
  }

  int* arr = (int*)malloc((sizeof(int) * get_size(stack)));
  int i = 0;
  for(Node* curr = stack->top; curr != NULL; curr = curr->next) {
    arr[i] = curr->data;
    i++;
  }
  return arr;
}

void push_array_to_stack(Stack* stack, int* array, int size) {
  for(int i = 0; i < size; i++) {
    push(stack, array[i]);
  }
}
