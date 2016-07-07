#ifndef _DEQUE_H_
#define _DEQUE_H_

typedef struct deque Deque;

Deque *deque_create(size_t size);

void deque_destroy(Deque * restrict deque);

void deque_clear(Deque * restrict deque);

bool deque_empty(const Deque * restrict deque);

size_t deque_size(const Deque * restrict deque);

void deque_push_front(Deque * restrict deque, const void * restrict source);

void deque_push_back(Deque * restrict deque, const void * restrict source);

void deque_front(const Deque * restrict deque, void * restrict dest);

void deque_back(const Deque * restrict deque, void * restrict dest);

void deque_pop_front(Deque * restrict deque);

void deque_pop_back(Deque * restrict deque);

#endif