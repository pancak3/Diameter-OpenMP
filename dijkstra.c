#include <assert.h>
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>

#define INFINITY INT_MAX
#define UNDEFINED INT_MIN

/**
 * Calculate the lengths of the shortest paths from a given node (src) to
 * every other node in the graph sequentially.
 * Size of array (*results) must be at least nnodes.
 */
void seq_sssp_dijkstra(int weights[][MAX], int src, int *results, int nnodes) {
    // keep track of which vertices have been visited
    bool *visited = malloc(nnodes * sizeof *visited);
    assert(visited);
    for (int i = 0; i < nnodes; i++)
        *results[i] = false;

    // keep track of the previous node for the shortest path
    int *prev = malloc(nnodes * sizeof *prev);
    assert(prev);
    for (int i = 0; i < nnodes; i++)
        *prev[i] = UNDEFINED;

    // initialise all non-source vertices to infinite distance
    for (int i = 0; i < nnodes; i++)
        *dists[i] = i == src ? 0 : INFINITY;

}

/**
 * Calculate the length of the shortest path between each pair of nodes in the
 * graph in parallel.
 * Size of array (*results) must be at least size nnodes * nnodes
 */
void para_apsp_dijkstra(int weights[][MAX], int src, int *results, int nnodes) {

}
