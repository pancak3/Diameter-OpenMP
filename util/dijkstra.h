/**
 * Header file for performing Dijkstra's Algorithm on a weighted directed graph.
 *
 * COMP90025 Parallel and Multicore Computing Assignment 1
 * Qifan Deng <qifand@student.unimelb.edu.au>
 * Alan Ung <alanu@student.unimelb.edu.au>
 * August 2019
 */

#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#define MAX 10000

/** Perform Dijkstra's Algorithm from node given by index src. */
void sssp_dijkstra(int adj_matrix[][MAX], int nnodes, int src, int *dists);

#endif // DIJKSTRA_H
