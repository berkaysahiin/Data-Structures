typedef struct Queue {
    int front;
    int rear;
    int size;
    int capacity;
    int *array;
}Queue;

Queue* init(int capacity);
void enqueue(Queue *q, int data);
void optimize(Queue *q);
int dequeue(Queue *q);
int isEmpty(Queue *q);
int isFull(Queue *q);
void printQueue(Queue *q);
void clear(Queue*);
void clear_and_free(Queue*);
void print_queue_array(Queue *queue);
