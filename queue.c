/**
 * Module for creating and operating on priority queues.
 */

#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "queue.h"

#define EXPAND_FACTOR 2  // factor to expand capacity of priority queue

typedef struct {
    int priority;
    int value;
} Node;

struct pQueue {
    Node *nodes;    // array of nodes in the queue
    int n;          // current size of queue
    int max;        // current capacity of queue
    int type;       // type of the priority queue (min/max)
};

// /* MAIN FUNCTION FOR TESTING ONLY */
//
// int main(void) {
//     PQueue *queue = pqueue_create(TYPE_MIN, 10);
//     pqueue_push(queue, 10, 0);
//     pqueue_push(queue, 5, 5);
//     pqueue_push(queue, 7, 3);
//     pqueue_push(queue, 4, 6);
//     pqueue_push(queue, 1, 9);
//     pqueue_push(queue, 8, 2);
//     pqueue_push(queue, 9, 1);
//     pqueue_push(queue, 3, 7);
//     pqueue_push(queue, 2, 8);
//     pqueue_push(queue, 6, 4);
//
//     for (int i = 0; i < 10; i++) {
//         int priority;
//         int value = pqueue_pop(queue, &priority);
//         printf("Priority %d, value %d\n", priority, value);
//     }
// }

/* PRIVATE FUNCTIONS */

void sift_up(PQueue *queue, int i);
void sift_down(PQueue *queue, int i);
bool check_parent(PQueue *queue, int i);
void node_swap(Node *n0, Node *n1);
int priority_child(PQueue *queue, int i);

/* MODULE FUNCTION DEFINITIONS */

PQueue *pqueue_create(int type, int init_size) {
    if (init_size < 1)
        return NULL;

    PQueue *queue = malloc(sizeof *queue);
    assert(queue);

    queue->nodes = malloc(init_size * sizeof *queue->nodes);
    assert(queue->nodes);
    queue->n = 0;
    queue->max = init_size;
    queue->type = type;

    return queue;
}

void pqueue_push(PQueue *queue, int value, int priority) {
    assert(queue);

    // expand queue if at max capacity
    if (queue->n == queue->max) {
        queue->max *= EXPAND_FACTOR;
        queue->nodes = realloc(queue->nodes, queue->max);
        assert(queue->nodes);
    }

    queue->nodes[queue->n].priority = priority;
    queue->nodes[queue->n].value = value;

    // sift up to restore heap property
    sift_up(queue, (queue->n)++);
}

int pqueue_pop(PQueue *queue, int *priority) {
    assert(queue && queue->n != 0);

    // store root node locally
    Node root = queue->nodes[0];

    // move last element to root position and sift down to restore heap property
    if (--(queue->n) > 0) {
        queue->nodes[0] = queue->nodes[queue->n];
        sift_down(queue, 0);
    }

    *priority = root.priority;
    return root.value;
}

int pqueue_size(PQueue *queue) {
    assert(queue);
    return queue->n;
}

void pqueue_delete(PQueue *queue) {
    if (!queue) return;
    free(queue->nodes);
    free(queue);
}

/* PRIVATE FUNCTION DEFINITIONS */

/** Start at node i and sift down until the heap property is restored */
void sift_up(PQueue *queue, int i) {
    assert(queue && queue->n >= i);
    while (!check_parent(queue, i)) {
        // swap this node with its parent
        node_swap(queue->nodes + i, queue->nodes + (i-1) / 2);
        i = (i-1) / 2;
    }
}

/** Start at node i and sift up until the heap property is restored */
void sift_down(PQueue *queue, int i) {
    assert(queue && queue->n >= i);

    int l = 2*i + 1;
    int r = 2*i + 2;

    // check if this is the last node (no children)
    if (l >= queue->n) return;

    // check if this node has a right child (need to compare children)
    if (r < queue->n) {
        int target = priority_child(queue, i);
        if (!check_parent(queue, target)) {
            node_swap(queue->nodes + i, queue->nodes + target);
            sift_down(queue, target);
        }

    } else if (!check_parent(queue, l)) {
        node_swap(queue->nodes + i, queue->nodes + l);
        sift_down(queue, l);
    }
}

/**
 * Return true if the heap property holds between node i and its parent.
 * If the node is the root, return true.
 */
bool check_parent(PQueue *queue, int i) {
    if (i == 0) return true;

    int child_priority = queue->nodes[i].priority;
    int parent_priority = queue->nodes[(i-1) / 2].priority;

    return (queue->type == TYPE_MIN && parent_priority < child_priority) ||
        (queue->type == TYPE_MAX && parent_priority > child_priority);
}

/** Swap two nodes. */
void node_swap(Node *n0, Node *n1) {
    Node temp = *n0;
    *n0 = *n1;
    *n1 = temp;
}

/**
 * Return the index of the higher/lower priority child (as applicable) of
 * node i.
 */
int priority_child(PQueue *queue, int i) {
    assert(queue && 2*i + 2 < queue->n);

    int l = 2*i + 1;
    int r = 2*i + 2;

    if (queue->type == TYPE_MIN)
        return (queue->nodes[r].priority < queue->nodes[l].priority) ? r : l;
    else
        return (queue->nodes[r].priority > queue->nodes[l].priority) ? r : l;
}
