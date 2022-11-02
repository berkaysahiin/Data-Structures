#ifndef Queue_circular
#define Queue_circular

typedef struct {
  int front; // index of the front element
  int rear; // index of the last element
  int capacity; // maximum number of elements in the queue
  int size; // current number of elements in the queue
  int *array; // pointer to the array containing the queue elements
} Queue;

Queue *init(int capacity); // initialize the queue

void enqueue(Queue *queue, int item); // add an item to the rear of the queue
void print_queue(Queue *queue); 
void delete_queue(Queue *queue);
void print_array(Queue* queue);
int dequeue(Queue *queue); // remove the front element from the queue
int is_empty(Queue *queue);
int is_full(Queue *queue); 

#endif