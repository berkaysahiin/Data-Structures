#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "graph.h"

typedef struct Graph graph;
typedef struct Graph_Node graph_node;
typedef struct Adjacent adjacent;

static graph_node* new_graph_node(int key);
static adjacent* new_adjacent(int key);
static graph_node* add_graph_node(graph* g, int key); // returns added graph_node
static adjacent* add_adjacent(graph_node* gn, int key); // return added adjacent
static graph_node* get_graph_node(graph* g, int key); // return NULL or existing graph_node
static adjacent* get_adjacent(graph_node*, int key);

struct Graph_Node {
  int key;
  adjacent* adjacent_root;
  graph_node* next;
};

struct Adjacent {
  int key;
  adjacent* next;
};

struct Graph {
  int count;
  graph_node* root;
};

graph* graph_new()
{
  graph* g = malloc(sizeof(graph));
  g->count = 0;
  g->root = NULL;
  return g;
}

void graph_add(graph* g, int from, int to)
{
  // if graph does not contain 'from' add it
  if(from == to) return;

  assert(g != NULL);

  graph_node* find = get_graph_node(g, to);

  if(find == NULL) {
    add_graph_node(g, to);
  }
  else {
    if(get_adjacent(find, from) != NULL) return;
  }

  find = get_graph_node(g, from);

  if(find == NULL) {
    graph_node* add = add_graph_node(g, from);
    add_adjacent(add, to);
  }
  else {
    add_adjacent(find, to);
  }
}

void graph_print(const graph* g)
{
  assert(g != NULL);
  for(graph_node* curr = g->root; curr != NULL; curr = curr->next) {
    printf("graph node key: %d, adjs: ", curr->key);
    for(adjacent* adj = curr->adjacent_root; adj != NULL; adj = adj->next) {
      printf("%d->", adj->key);
    }
    printf("\n");
  }
}

void graph_vis(const graph* g)
{
  assert(g != NULL);
  FILE* fp = fopen("src/dotfiles/vis.dot", "w");
  assert(fp != NULL);

  fprintf(fp, "digraph {\n");
  for(graph_node* curr = g->root; curr != NULL; curr = curr->next) {
    for(adjacent* adj = curr->adjacent_root; adj != NULL; adj = adj->next) {
      fprintf(fp, "%d -> %d\n", curr->key, adj->key);
    }
  }
  fprintf(fp, "}");
}

int graph_size(const graph* g)
{
  assert(g != NULL);

  int count = 0;
  for(graph_node* curr = g->root; curr != NULL; curr = curr->next) {
    count++;
  }

  return count;
}

int graph_edgeNum(const graph* g)
{
  assert(g != NULL);
  int count = 0;

  for(graph_node* curr = g->root; curr != NULL; curr = curr->next) {
    for(adjacent* adj = curr->adjacent_root; adj != NULL; adj = adj->next) {
      count++;
    }
  }
  return count;
}

int graph_max_edgeNum(const graph* g)
{
  int n = graph_size(g);
  return (n*(n-1)) / 2; 
}

graph* graph_path(const graph* g, int from, int to)
{
  UNIMPLEMENTED;
}

//---------------------------------PRIVATE------------------------------------------

static graph_node* get_graph_node(graph* g, int key) // return NULL or existing graph_node
{
  assert(g != NULL);
  for(graph_node* curr = g->root; curr != NULL; curr = curr->next) {
    if(curr->key == key) return curr;
  }
  return NULL;
}

static adjacent* get_adjacent(graph_node* g, int key) 
{
  assert(g != NULL);
  for(adjacent* adj = g->adjacent_root; adj != NULL; adj = adj->next) {
    if(adj->key == key) return adj;
  }
  return NULL;
}

static graph_node* new_graph_node(int key) 
{
  graph_node* gn = malloc(sizeof(graph_node));
  gn->key = key;
  gn->next = NULL;
  gn->adjacent_root = NULL;
  return gn;
}

static adjacent* new_adjacent(int key) 
{
  adjacent* adj = malloc(sizeof(adjacent));
  adj->key = key;
  adj->next = NULL;
  return adj;
}

static graph_node* add_graph_node(graph* g, int key) // returns added graph_node
{
  assert(g != NULL);

  if(g->root == NULL) {
    g->root = new_graph_node(key);
    return g->root;
  }
  
  graph_node* curr;
  for(curr = g->root; curr->next != NULL; curr = curr->next);
  curr->next = new_graph_node(key);

  return curr->next;
}

static adjacent* add_adjacent(graph_node* gn, int key) // return added adjacent
{
  assert(gn != NULL);
  if(get_adjacent(gn, key) != NULL) return NULL;

  if(gn->adjacent_root == NULL) {
    gn->adjacent_root = new_adjacent(key);
    return gn->adjacent_root;
  }

  adjacent* curr;
  for(curr = gn->adjacent_root; curr->next != NULL; curr = curr->next);
  curr->next = new_adjacent(key);

  return curr->next;
}

