#include <stdio.h>
#include "graph.h"
#include <assert.h>

int main() 
{
  graph* g = new_graph(10);
  add_edge(g, 1, 2);
  add_edge(g, 2, 3);
  add_edge(g, 4, 1);
  add_edge(g, 9, 5);
  add_edge(g, 5, 8);
  add_edge(g, 8, 6);
  add_edge(g, 4, 7);
  add_edge(g, 1, 4);

  delete_edge(g, 1, 2);
  delete_edge(g, 2, 3);
  delete_edge(g, 4, 1);
  delete_edge(g, 9, 5);
  delete_edge(g, 1, 4);

  print_graph(g);
}
