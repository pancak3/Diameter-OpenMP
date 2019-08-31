/**
 * Module for performing Dijkstra's Algorithm on a weighted directed graph.
 *
 * COMP90025 Parallel and Multicore Computing Assignment 1
 * Qifan Deng <qifand@student.unimelb.edu.au>
 * Alan Ung <alanu@student.unimelb.edu.au>
 * August 2019
 */

#include <assert.h>
#include <limits.h>

#include "dijkstra.h"
#include "heap.h"

#define NOT_CONNECTED INT_MAX
#define INFINITY INT_MAX

/* PUBLIC FUNCTION DEFINITIONS */

void sssp_dijkstra(int adj_matrix[][MAX], int nnodes, int src, int *dists) {
    assert(nnodes > 0 && src < nnodes);

    // create min heap as priority queue and add source node
    Heap *queue = new_heap(TYPE_MIN);
    heap_push(queue, src, 0);

    // set dist for source as 0 and all other nodes as INFINITY
    for (int i = 0; i < nnodes; i++)
        dists[i] = i == src ? 0 : INFINITY;

    while (!heap_is_empty(queue)) {
        // index and distance of closest node in queue
        int curr_node, curr_dist;
        curr_node = heap_pop(queue, &curr_dist);

        // check distances for all neighbours
        for (int i = 0, new_dist; i < nnodes; i++) {
            if ((new_dist = curr_dist + adj_matrix[curr_node][i]) < dists[i]) {
                heap_push(queue, i, new_dist);
                dists[i] = new_dist;
            }
        }
    }
}
