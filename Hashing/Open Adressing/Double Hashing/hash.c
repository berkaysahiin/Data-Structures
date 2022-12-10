#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <stdlib.h>
#include "random_number_generator.h"

//---------DOUBLE HASHING----------------

#define TABLE_SIZE 100
#define EMPTY 0
#define USED 1
#define DELETED 2

typedef struct {
  int key;
  int is_used;
}entry;

uint32_t hash(int key);
uint32_t second_hash(int key);
void insert_key(entry table[], int key);
void remove_key(entry table[], int key);
void print_table(entry table[]);

uint32_t hash(int key) 
{
  return xor_shift(key) % TABLE_SIZE;
}

uint32_t second_hash(int key) 
{
  return xor_shift(xor_shift(key)) % TABLE_SIZE;
}

void insert_key(entry table[], int key)
{
  uint32_t index = hash(key);
  uint32_t v = second_hash(key);

  for(int i = 0; i < TABLE_SIZE ; i++) {
    index = (index + i*v) % TABLE_SIZE;
    if(table[index].is_used == EMPTY || table[index].is_used == DELETED) break;
  }

  if(table[index].is_used == USED) {
    printf("Could not found a proper bucket to insert key: %d\n", key);
    return;
  }

  table[index].key = key;
  table[index].is_used = USED;
}

void remove_key(entry table[], int key)
{
  uint32_t index = hash(key);
  uint32_t v = second_hash(key);

  for(int i = 0; i < TABLE_SIZE; i++) {
    index = (index + i*v) % TABLE_SIZE;
    if(table[index].is_used == EMPTY) return;
    if(table[index].is_used == USED && table[index].key == key) {
      table[index].is_used = DELETED;
    }
  }
}

void print_table(entry table[])
{
  for(int i = 0; i < TABLE_SIZE; i++) {
    if(table[i].is_used == USED) {
      printf("at %d -> ::%d::", i, table[i].key);
    }
    else if (table[i].is_used == EMPTY) {
      printf("EMPTY");
    }
    else if(table[i].is_used == DELETED) {
      printf("DELETED");
    }
    printf("\n");
  }
}

