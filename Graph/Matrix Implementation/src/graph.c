#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "graph.h"

struct graph {
  int n;
  int **matrix;
};

typedef struct graph graph;

graph* new_graph(size_t num_vertex)
{
  graph* g = calloc(1, sizeof(graph));
  g->n = num_vertex;
  g->matrix = calloc(num_vertex, sizeof(int));
  for(int i = 0; i < num_vertex; i++) {
    g->matrix[i] = calloc(num_vertex, sizeof(int));
  }
  return g;
}

void print_graph(const graph* g)
{
  FILE* fp = fopen("src/dotfiles/vis.dot", "w");
  assert(fp != NULL);
  int n = g->n;
  fprintf(fp, "graph {\n");

  for(int i = 0; i < n; i++) {
    for(int j = 0; j < n; j++) {
      if(g->matrix[i][j] == 1)
      fprintf(fp, "%d -- %d\n",i ,j);
    }
  }

  fprintf(fp, "}\n");
}

int get_edge(const graph* g, int from, int to) 
{
  return g->matrix[from][to];
}

void add_edge(graph* g, int from, int to) 
{
  assert(from < g->n && to < g->n);
  if(get_edge(g, from, to)) return;

  g->matrix[from][to] = 1;
}

void delete_edge(graph* g, int from, int to)
{
  assert(from < g->n && to < g->n);
  if(get_edge(g, from, to) == 0) return;
  g->matrix[from][to] = 0;
}

