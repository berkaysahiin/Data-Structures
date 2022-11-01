struct Node 
{
  int data;
  struct Node* next;
};
typedef struct Node Node;

struct Stack
{
  Node* top;
};
typedef struct Stack Stack;

Stack* init(void);
void memberwise_copy(Stack*, Stack);
void clear(Stack*);
void free_stack(Stack*);
void print_stack(Stack* stack);
void push(Stack* stack, int data);
int pop(Stack* stack);
int peek(Stack* stack);
void reverse(Stack* stack);
int is_empty(Stack* stack);
int contains(Stack* stack, int data); // return 1 if data is in stack, 0 otherwise
int equal(Stack* stack1, Stack* stack2); // return 1 if stack1 and stack2 are equal, 0 otherwise
int get_size(Stack*);
void push_array_to_stack(Stack* stack, int* array, int size);
int* to_array(Stack* stack);
