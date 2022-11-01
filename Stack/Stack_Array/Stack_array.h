#ifndef Stack_array
#define Stack_array

typedef struct Stack {
  int* arr;
  int capacity; // array size
  int top; // index of the last element
}Stack;

Stack* init(int capacity);
Stack* clone(Stack stack);  
void push(Stack*, int);
int pop(Stack*);
int peek(Stack);
int is_full(Stack);
int is_empty(Stack);
int is_equal(Stack, Stack);
void reverse(Stack*); // not implemented
void clear(Stack*);
void clear_and_free(Stack*);
void print_stack(Stack stack);

#endif 