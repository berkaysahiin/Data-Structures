#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <stdlib.h>
#include "random_number_generator.h"

//---------LINEAR PROBING------------

#define TABLE_SIZE 100

typedef struct {
  int key;
  int is_used;
}entry;

uint32_t hash(int key);
void insert_key(entry table[], int key);
void remove_key(entry table[], int key);
void print_table(entry table[]);

uint32_t hash(int key) 
{
  return xor_shift(key) % TABLE_SIZE;
}

void insert_key(entry table[], int key)
{
  uint32_t index = hash(key);
  for(int i = 0; i < TABLE_SIZE; i++) {
    if(table[index].is_used == 0) break;
    index = (index + 1) % TABLE_SIZE;
  }
  assert(table[index].is_used == 0);
  table[index].key = key;
  table[index].is_used = 1;
}

void remove_key(entry table[], int key)
{
  uint32_t index = hash(key);
  for(int i = 0; i < TABLE_SIZE; i++) {
    if(table[index].key == key) {
      table[index].is_used = 0;
      return;
    }
    index = (index + 1) % TABLE_SIZE;
  }
}

void print_table(entry table[])
{
  for(int i = 0; i < TABLE_SIZE; i++) {
    if(table[i].is_used == 1) {
      printf("at %d -> ::%d::", i, table[i].key);
    }
    else {
      printf("EMPTY");
    }
    printf("\n");
  }
}

