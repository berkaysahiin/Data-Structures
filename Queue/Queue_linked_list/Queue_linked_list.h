typedef struct Node {
  int data;
  struct Node *next;
}Node;

typedef struct Queue {
  struct Node *front;
  struct Node *rear;
}Queue;

Queue* init_queue();
Queue* clone(Queue*);

int* to_array(Queue*);
int dequeue(Queue*);
int is_empty(Queue*); // returns 1 if its empty, 0 otherwise
int is_equal(Queue*, Queue*);
int contains(Queue*, int); 
int peek(Queue*); // Returns the int at the beginning of the queue without removing it.

void enqueue(Queue* ,int);
void print_queue(Queue*);
void clear(Queue*);
void reverse(Queue*);




