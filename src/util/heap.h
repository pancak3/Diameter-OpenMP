/* *
 * Header file for creating and manipulating binary heaps of integer data.
 *
 * COMP90025 Parallel and Multicore Computing Assignment 1
 * Qifan Deng <qifand@student.unimelb.edu.au>
 * Alan Ung <alanu@student.unimelb.edu.au>
 * August 2019
 *
 * Originally created for COMP20007 Design of Algorithms Assignment 1
 * Alan Ung <alanu@student.unimelb.edu.au>, March 2017
 */

#ifndef HEAP_H
#define HEAP_H

#include <stdbool.h>

#define TYPE_MIN 0  // to create a min heap
#define TYPE_MAX 1  // to create a max heap

typedef struct heap Heap;

/** Create and return a pointer to a heap. */
Heap *new_heap(int type);

/** Push an element onto the heap. */
void heap_push(Heap *heap, int priority, int data);

/**
 * Remove and return the lowest (min heap)/highest (max heap) priority data.
 * Assigns the priority of the returned element to *priority.
 */
int heap_pop(Heap *heap, int *priority);

/** Return the number of elements currently in a heap. */
int heap_size(Heap *heap);

/** Return true if a heap contains no entries, otherwise return false. */
bool heap_is_empty(Heap *heap);

/** Destroy and release the memory of a heap. */
void free_heap(Heap *heap);

#endif // HEAP_H
