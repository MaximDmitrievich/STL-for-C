#ifndef _PRIORITY_QUEUE_H_
#define _PRIORITY_QUEUE_H_

typedef struct priority_queue PriorityQueue;

PriorityQueue *priority_queue_create(size_t size, int (*compar)(const void *, const void *));

void priority_queue_destroy(PriorityQueue * restrict priority_queue);

void priority_queue_clear(PriorityQueue * restrict priority_queue);

bool priority_queue_empty(const PriorityQueue * restrict priority_queue);

size_t priority_queue_size(const PriorityQueue * restrict priority_queue);

void priority_queue_push(PriorityQueue * restrict priority_queue, const void * restrict source);

void priority_queue_front(const PriorityQueue * restrict priority_queue, void * restrict dest);

void priority_queue_pop(PriorityQueue * restrict priority_queue);

#endif