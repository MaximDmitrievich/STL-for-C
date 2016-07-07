#ifndef _QUEUE_H_
#define _QUEUE_H_

typedef struct queue Queue;

Queue *queue_create(size_t size);

void queue_destroy(Queue * restrict queue);

void queue_clear(Queue * restrict queue);

bool queue_empty(const Queue * restrict queue);

size_t queue_size(const Queue * restrict queue);

void queue_push(Queue * restrict queue, const void * restrict source);

void queue_front(const Queue * restrict queue, void * restrict dest);

void queue_pop(Queue * restrict queue);

#endif