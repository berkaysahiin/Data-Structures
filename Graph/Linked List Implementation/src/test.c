#include <stdio.h>
#include "graph.h"
#include <assert.h>

int main() 
{
  graph* g = graph_new();
  
  for(int i = 0; i < 7; i++) {
    for(int j = 0; j < 7; j++) {
      graph_add(g, i, j);
    }
  }
  
  printf("size: %d\n", graph_size(g));
  printf("edge: %d\n", graph_edgeNum(g));
  printf("max edge: %d\n", graph_max_edgeNum(g));
  graph_vis(g);
}
