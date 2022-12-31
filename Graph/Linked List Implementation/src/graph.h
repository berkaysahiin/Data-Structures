// linked list implementation
#ifndef _GRAPH_H
#define _GRAPH_H

#define UNIMPLEMENTED \
    do { \
        fprintf(stderr, "%s:%d: %s is not implemented yet\n", \
                __FILE__, __LINE__, __func__); \
        abort(); \
    } while(0)

typedef struct Graph graph;

graph* graph_new();
void graph_add(graph* g, int from, int to); // add edge
void graph_print(const graph*); // print graph
void graph_vis(const graph*); // pipe graph into dot

int graph_size(const graph*);
int graph_edgeNum(const graph*);
int graph_max_edgeNum(const graph*);

graph* graph_path(const graph*, int from, int to);
//----------------------------traversal functions----------------------------

#endif // _GRAPH_H
