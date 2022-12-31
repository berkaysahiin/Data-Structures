// adjacency matrix implementation
#ifndef _GRAPH_H
#define _GRAPH_H

typedef struct graph graph;

graph* new_graph(size_t num_vertex); // inits graph with square matrix with n = num_vertex
int get_edge(const graph*, int from, int to);
void print_graph(const graph*);
void add_edge(graph*, int from, int to);
void delete_edge(graph*, int from, int to);

#endif // _GRAPH_H
