#include <stdio.h>
#include <stdlib.h>
#include "Queue_circular.h"

int main(void) {
  Queue *queue = init(5);
  enqueue(queue, 1);
  enqueue(queue, 2);
  enqueue(queue, 3);
  enqueue(queue, 4);
  enqueue(queue, 5);
  print_queue(queue);
  print_array(queue);
  dequeue(queue);
  print_queue(queue);
  print_array(queue);
  enqueue(queue, 6);
  print_queue(queue);
  print_array(queue);
  delete_queue(queue);
  return 0;
}

Queue *init(int capacity) {
  if(capacity <= 0) {
    printf("Invalid capacity, Returning NULL");
    return NULL;
  }

  Queue *queue = (Queue *)malloc(sizeof(Queue));
  queue->capacity = capacity;
  queue->front = -1;
  queue->rear = -1;
  queue->size = 0;
  queue->array = (int *)malloc(sizeof(int) * capacity);
  return queue;
}

void print_queue(Queue *queue) {
  if(queue == NULL) {
    printf("Queue is NULL, Returning");
    return;
  }

  if(is_empty(queue)) {
    printf("Queue is empty");
    return;
  }
  printf("\nqueue-> ");
  int i = queue->front;
  while(i != queue->rear) {
    printf("%d ", queue->array[i]);
    i = (i + 1) % queue->capacity;
  }
  printf("%d ", queue->array[i]);  
}

void print_array(Queue* queue) {
  if(queue == NULL) {
    printf("Queue is NULL, Returning");
    return;
  }
  
  printf("\narray-> ");
  int i = 0;
  while(i != queue->capacity) {
    printf("%d ", queue->array[i]);
    i++;
  }
}

void enqueue(Queue *queue, int item) {
  if(queue == NULL) {
    printf("Queue is NULL, Returning");
    return;
  }

  if(is_full(queue)) {
    printf("Queue is full, Returning");
    return;
  }

  if(is_empty(queue)) {
    queue->front = 0;
    queue->rear = 0;
    queue->array[queue->rear] = item;
    queue->size++;
    return;
  }

  queue->rear = (queue->rear + 1) % queue->capacity;
  queue->array[queue->rear] = item;
  queue->size++;
}

int dequeue(Queue *queue) {
  if(queue == NULL) {
    printf("Queue is NULL, Returning");
    return -1;
  }

  if(is_empty(queue)) {
    printf("Queue is empty, Returning");
    return -1;
  }

  int item = queue->array[queue->front];
  queue->front = (queue->front + 1) % queue->capacity;
  queue->size--;
  return item;
}

void delete_queue(Queue *queue) {
  if(queue == NULL) {
    printf("Queue is NULL, Returning");
    return;
  }

  free(queue->array);
  free(queue);
}

int is_empty(Queue *queue) {
  if(queue == NULL) {
    printf("Queue is NULL, Returning");
    return -1;
  }
  return queue->size == 0;
}

int is_full(Queue *queue) {
  if(queue == NULL) {
    printf("Queue is NULL, Returning");
    return -1;
  }
  return queue->size == queue->capacity;
}
