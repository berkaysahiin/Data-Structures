#include <stdio.h>
#include <stdlib.h>
#include "Queue_linear_array.h"

int main(void) {
  Queue* queue = init(2);
  for(int i = 0; i < 30; i++) {
    enqueue(queue, i);
  } 
  print_queue_array(queue);
  printf("\ndequed: ");
  for(int i = 0; i < 25; i++) {
    printf("%d ", dequeue(queue));
  } 
  printf("\nafter dequeue new queue is: ");
  printQueue(queue);
  printf("\nbefore optimize queue array is: ");
  print_queue_array(queue);
  optimize(queue);
  printf("\nafter optimize new queue array is: ");
  print_queue_array(queue);
  enqueue(queue, 100);
  enqueue(queue, 200);
  enqueue(queue, 300);
  enqueue(queue, 400);
  enqueue(queue, 500);
  printf("\nafter some enqueue new queue array is: ");
  print_queue_array(queue);
  printf("\nfinal queue: ");
  printQueue(queue);
}

Queue* init(int capacity) {
  if(capacity <= 0) {
    return NULL;
  }

  Queue* queue = (Queue*)malloc(sizeof(Queue));
  queue->front = -1;
  queue->rear = -1;
  queue->size = 0;
  queue->capacity = capacity;
  queue->array = (int*)malloc(sizeof(int) * capacity);

  return queue;
}

void enqueue(Queue* queue, int data) {
  if(queue == NULL) {
    printf("Queue is not initialized\n");
    return;
  }

  if(isEmpty(queue)) {
    queue->front = 0;
    queue->rear = 0;
    queue->array[queue->rear] = data;
    queue->size++;
    return;
  }

  if(isFull(queue)) {
    queue->capacity *= 2;
    queue->array = (int*)realloc(queue->array, sizeof(int) * queue->capacity);
  }

  queue->array[++queue->rear] = data;
  queue->size++;
}

void printQueue(Queue* queue) {
  if(queue == NULL) {
    printf("Queue is not initialized\n");
    return;
  }

  if(isEmpty(queue)) {
    printf("Queue is empty\n");
    return;
  }

  for(int i = queue->front; i < queue->rear + 1; i++) {
    printf("%d ", queue->array[i]);
  }
}

void print_queue_array(Queue* queue) {
  if(queue == NULL) {
    printf("Queue is not initialized\n");
    return;
  }

  if(isEmpty(queue)) {
    printf("Queue is empty\n");
    return;
  }
  printf("array size: %d, array capacity: %d -> ", queue->size, queue->capacity);
  for(int i = 0; i < queue->capacity; i++) {
    printf("%d ", queue->array[i]);
  }
}

void optimize(Queue *q) {
  if(q == NULL) {
    printf("Queue is not initialized\n");
    return;
  }
 
  if(q->front == 0 || q->front == -1) {
    return;
  }

  for(int i = 0; i < q->size; i++) {
    q->array[i] = q->array[q->front + i];
  }

  q->rear = q->size - 1;
  q->front = 0;

  if(q->size < q->capacity / 4) {
    q->capacity /= 2;
    q->array = (int*)realloc(q->array, sizeof(int) * q->capacity);
  }

}

void clear(Queue* queue) {
  if(queue == NULL) {
    printf("Queue is not initialized\n");
    return;
  }
  queue->front = -1;
  queue->rear = -1;
  queue->size = 0;
  free(queue->array);
}

void clear_and_free(Queue* queue) {
  if(queue == NULL) {
    printf("Queue is not initialized\n");
    return;
  }
  queue->front = -1;
  queue->rear = -1;
  queue->size = 0;
  free(queue->array);
  free(queue);
}

int isEmpty(Queue* queue) {
  return queue->size == 0;
}

int isFull(Queue* queue) {
  return queue->size == queue->capacity;
}

int dequeue(Queue* queue) { 
  if(queue == NULL) {
    printf("Queue is NULL");
    return -1;
  }

  if(isEmpty(queue)) {
    printf("Queue is empty");
    return -1;
  }

  if(queue->front == 0 && queue->rear == 0) {
    printf("this worked");
    int data = queue->array[queue->front];
    queue->front = -1;
    queue->rear = -1;
    queue->size--;
    return data;
  }

  queue->size--;
  return queue->array[queue->front++];
}