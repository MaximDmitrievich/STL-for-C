#ifndef _STACK_H_
#define _STACK_H_

typedef struct stack Stack;

Stack *stack_create(size_t size);

void stack_destroy(Stack * restrict stack);

void stack_clear(Stack * restrict stack);

bool stack_empty(const Stack * restrict stack);

size_t stack_size(const Stack * restrict stack);

void stack_push(Stack * restrict stack, const void * restrict source);

void stack_top(const Stack * restrict stack, void * restrict dest);

void stack_pop(Stack * restrict stack);

#endif