#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "random_number_generator.h"

#define TABLE_SIZE 100

int hash(int key);
void insert_key(Node* table[], int key);
void remove_key(Node* table[], int key);
void print_table(Node* hash_table[]);

int hash(int key) 
{
  return xor_shift(key) % TABLE_SIZE;
}

void insert_key(Node* hash_table[], int key)
{
  uint32_t index = hash(key);
  linked_list_insert_end(&hash_table[index], key);
}

void remove_key(Node* hash_table[], int key)
{
  int index = hash(key);
  if(hash_table[index] == NULL) return;
  linked_list_remove_element(&hash_table[index], key);
}

void print_table(Node* hash_table[]) 
{
  for(int i = 0; i < TABLE_SIZE; ++i) {
    if(hash_table[i] == NULL) {
      printf("EMPTY");
    }
    else {
      linked_list_print(hash_table[i]);
    }
    printf("\n");
  }
}

