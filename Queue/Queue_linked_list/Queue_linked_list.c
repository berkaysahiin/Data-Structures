#include <stdio.h>
#include <stdlib.h>
#include "Queue_linked_list.h"

int main() {
  Queue* my_queue = init_queue();
  enqueue(my_queue, 31);
  enqueue(my_queue, 69);
  enqueue(my_queue, 100);
  enqueue(my_queue, 200);
  enqueue(my_queue, 412);
 
  reverse(my_queue);

  print_queue(my_queue);
}

Queue* init_queue() {
  Queue* q = (Queue*)malloc(sizeof(Queue));
  q->front = NULL;
  q->rear = NULL;;
  return q;
}

void print_queue(Queue *q) {
  for(Node* curr = q->front; curr != NULL; curr = curr->next) {
    printf("%d ", curr->data);
  }
}

int is_empty(Queue *q) {
  return q->front == NULL;
}

void enqueue(Queue *q, int data) {
  Node* new_node = (Node*)malloc(sizeof(Node));
  new_node->data = data;
  new_node->next = NULL;
  if (q->front == NULL) {
    q->front = new_node;
    q->rear = new_node;
    return;
  }

  q->rear->next = new_node;
  q->rear = new_node;
}

int dequeue(Queue *q) {
  if (q->front == NULL) {
    printf("Queue is empty, cannot dequeue");
    return -1;
  }
  
  Node* front_node = q->front;
  int return_value = front_node->data;
  q->front = front_node->next;
  free(front_node);

  if(q->front == NULL) {
    q->rear = NULL;
  }

  return return_value;
}

int peek(Queue* q) {
  return q->front->data;
}

int contains(Queue* q, int data) {
  for(Node* curr = q->front; curr != NULL; curr = curr->next) {
    if (curr->data == data) {
      return 1;
    }
  }
  return 0;
}

int is_equal(Queue* q1, Queue* q2) {
  if (q1->front == NULL && q2->front == NULL) {
    return 1;
  }

  if (q1->front == NULL || q2->front == NULL) {
    return 0;
  }

  Node* curr1 = q1->front;
  Node* curr2 = q2->front;

  while(curr1 != NULL && curr2 != NULL) {
    if (curr1->data != curr2->data) {
      return 0;
    }
    curr1 = curr1->next;
    curr2 = curr2->next;
  }

  if (curr1 != NULL || curr2 != NULL) {
    return 0;
  }

  return 1;
}

void clear(Queue* q) {
  while(!is_empty(q)) {
    dequeue(q);
  }

  q->front = NULL;
  q->rear = NULL;
}

void reverse(Queue* q) {
  Node* curr = q->front;
  Node* initial_front = curr;
  Node* prev = NULL;

  while(curr != NULL) {
    Node* next = curr->next;
    curr->next = prev;
    prev = curr;
    curr = next;
  }

  q->front = prev;
  q->rear = initial_front;
}