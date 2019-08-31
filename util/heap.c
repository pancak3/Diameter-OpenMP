/* *
 * Module for creating and manipulating binary heaps of integer data.
 *
 * COMP90025 Parallel and Multicore Computing Assignment 1
 * Qifan Deng <qifand@student.unimelb.edu.au>
 * Alan Ung <alanu@student.unimelb.edu.au>
 * August 2019
 *
 * Originally created for COMP20007 Design of Algorithms Assignment 1
 * Alan Ung <alanu@student.unimelb.edu.au>, March 2017
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "heap.h"

#define INIT 5      // initial capacity of heap
#define GROW 2      // factor to reallocate dynamic array
#define INTACT 0    // heap property is intact
#define BROKEN 1    // heap property is broken

typedef struct {
    int data;
    int priority;
} Node;

struct heap {
    Node *nodes;    // pointer to array of nodes
    int n;          // current size of heap (nodes in dynamic array)
    int max;        // current capacity of heap
    int type;       // min heap/max heap
};

/* PRIVATE FUNCTION PROTOTYPES */

void grow_heap(Heap *heap);
int check_parent(Heap *heap, int child_locn);
void sift_up(Heap *heap, int node_locn);
void sift_down(Heap *heap, int node_locn);
void swap_nodes(Heap *heap, int locn_a, int locn_b);
int priority_child(Heap *heap, int parent_locn);

/* PUBLIC FUNCTION DEFINITIONS */

Heap *new_heap(int type) {
    Heap *heap = malloc(sizeof(*heap));
    assert(heap);

    heap->n = 0;
    heap->max = INIT;
    heap->type = type;

    heap->nodes = malloc(heap->max * sizeof(*(heap->nodes)));
    assert(heap->nodes);

    return heap;
}

void heap_push(Heap *heap, int data, int priority) {
    assert(heap);

    // reallocate memory if insertion would exceed array bounds
    if (heap->n + 1 >= heap->max)
        grow_heap(heap);

    int new_locn = heap->n++;   // next available slot in the heap

    // initially insert into the next available slot
    heap->nodes[new_locn].data = data;
    heap->nodes[new_locn].priority = priority;

    // restore the heap property
    sift_up(heap, new_locn);
}

int heap_pop(Heap *heap, int *priority) {
    assert(heap && !heap_is_empty(heap));

    // store the root node before overwriting
    Node root = heap->nodes[0];

    heap->n--;
    if (!heap_is_empty(heap)) {
        // overwrite the root with the last node and update the heap size
        heap->nodes[0] = heap->nodes[heap->n];
        // restore the heap property
        sift_down(heap, 0);
    }

    #ifdef DEBUG
    printf("root.priority = %d\n", root.priority);
    #endif // DEBUG

    *priority = root.priority;
    return root.data;
}

int heap_size(Heap *heap) {
    return heap->n;
}

bool heap_is_empty(Heap *heap) {
    return heap_size(heap) == 0;
}

void free_heap(Heap *heap) {
    if (!heap)
        return;

    // first free the array of nodes
    free(heap->nodes);
    heap->nodes = NULL;

    // free the actual heap struct
    free(heap);
    heap = NULL;
}

/* * * *
 * PRIVATE FUNCTION DEFINITIONS
 */

// expand the capacity of a heap by reallocating the array of nodes
void grow_heap(Heap *heap) {
    assert(heap);

    heap->max *= GROW;
    Node *new = realloc(heap->nodes, heap->max * sizeof(*new));
    assert(new);

    heap->nodes = new;
}

// check the heap property between a given node and its parent only.
// returns INTACT if the heap property holds or the node is the root,
// otherwise returns BROKEN
int check_parent(Heap *heap, int child_locn) {
    assert(heap);

    if (child_locn == 0)     // root node - no parent
        return INTACT;

    // n = parent has children 2n + 1 and 2n + 2
    int parent_locn = (child_locn - 1) / 2;

    int child_priority = heap->nodes[child_locn].priority;
    int parent_priority = heap->nodes[parent_locn].priority;

    if ((heap->type == TYPE_MIN && child_priority < parent_priority) ||
        (heap->type == TYPE_MAX && child_priority > parent_priority))
        return BROKEN;

    return INTACT;
}

// restore the heap property by repeatedly moving a node upwards if necessary
void sift_up(Heap *heap, int node_locn) {
    int parent_locn;
    while (check_parent(heap, node_locn) == BROKEN) {
        parent_locn = (node_locn - 1) / 2;
        swap_nodes(heap, node_locn, parent_locn);
        node_locn = parent_locn;    // the entry is now in the parent position
    }
}

// restore the heap property by recursively moving a node downwards if necessary
void sift_down(Heap *heap, int node_locn) {
    assert(heap && node_locn < heap_size(heap));

    int left_locn = (2 * node_locn) + 1;  // potential left child location
    int rght_locn = (2 * node_locn) + 2;  // potential right child location


    if (left_locn >= heap->n)
        // no children - cannot sift down
        return;

    if (rght_locn < heap->n) {
        // two children - get the min/max priority child
        int target_locn = priority_child(heap, node_locn);

        // for min heap, compare parent to the min priority child
        if (check_parent(heap, target_locn) == BROKEN) {
            swap_nodes(heap, node_locn, target_locn);
            sift_down(heap, target_locn);
        }

    } else if (check_parent(heap, left_locn) == BROKEN) {
        // only left child exists and does not satisfy heap property
        swap_nodes(heap, node_locn, left_locn);
        sift_down(heap, left_locn);
    }
}

// swap the positions of two nodes in a heap
void swap_nodes(Heap *heap, int locn_a, int locn_b) {
    Node temp = heap->nodes[locn_a];
    heap->nodes[locn_a] = heap->nodes[locn_b];
    heap->nodes[locn_b] = temp;
}

// return the index of the min/max priority (for min/max heap) of two children.
// if equal priority, returns the index of the left child
int priority_child(Heap *heap, int parent_locn) {
    // assert heap exists and n = parent has 2 children (right child = 2n + 2)
    assert(heap && (2 * parent_locn) + 2 < heap_size(heap));

    int left_locn = (2 * parent_locn) + 1;  // location of left child
    int rght_locn = (2 * parent_locn) + 2;  // location of right child

    if (heap->type == TYPE_MIN) {
        // require the lower priority child
        if (heap->nodes[rght_locn].priority < heap->nodes[left_locn].priority)
            return rght_locn;
        return left_locn;

    } else {
        // require the higher priority child
        if (heap->nodes[rght_locn].priority > heap->nodes[left_locn].priority)
            return rght_locn;
        return left_locn;
    }
}
