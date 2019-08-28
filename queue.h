/**
 * Header file for module for priority queue module.
 */

#ifndef QUEUE_H
#define QUEUE_H

#define TYPE_MIN 0  // to create a min priority queue
#define TYPE_MAX 1  // to create a max priority queue

typedef struct pQueue PQueue;

/**
 * Return a pointer to a new priority queue.
 */
PQueue *pqueue_create(int type, int init_size);

/**
 * Push a new value with associated priority into the priority queue.
 */
void pqueue_push(PQueue *queue, int priority, int value);

/**
 * Return the highest/lowest priority value (as applicable) and delete it
 * from the priority queue. The priority is assigned to *priority.
 */
int pqueue_pop(PQueue *queue, int *priority);

/**
 * Return the number of elements in the priority queue.
 */
int pqueue_size(PQueue *queue);

/**
 * Delete a priority queue and release its associated memory.
 */
void pqueue_delete(PQueue *queue);

#endif // HEAP_H
