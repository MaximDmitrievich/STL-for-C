#include <signal.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"

typedef struct stack_node StackNode;

struct stack_node
{
	void *data;
	StackNode *next;
};

struct stack
{
	size_t size;
	StackNode *head;
};

Stack *stack_create(size_t size)
{
	if (!size)
	{
		return NULL;
	}

	Stack *stack = malloc(sizeof(Stack));
	if (stack == NULL)
	{
		return NULL;
	}

	stack->size = size;
	stack->head = NULL;

	return stack;
}

void stack_destroy(Stack * restrict stack)
{
	if (stack == NULL)
	{
		raise(SIGSEGV);
		return;
	}

	register StackNode *temp = stack->head;
	while (temp != NULL)
	{
		StackNode *local_temp = temp->next;

		free(temp->data);
		free(temp);

		temp = local_temp;
	}

	free(stack);
}

void stack_clear(Stack * restrict stack)
{
	if (stack == NULL)
	{
		raise(SIGSEGV);
		return;
	}

	register StackNode *temp = stack->head;
	stack->head = NULL;
	while (temp != NULL)
	{
		StackNode *local_temp = temp->next;

		free(temp->data);
		free(temp);

		temp = local_temp;
	}
}

bool stack_empty(const Stack * restrict stack)
{
	if (stack == NULL)
	{
		raise(SIGSEGV);
		return true;
	}

	return stack->head == NULL;
}

size_t stack_size(const Stack * restrict stack)
{
	if (stack == NULL)
	{
		raise(SIGSEGV);
		return (size_t) -1;
	}

	register StackNode *temp = stack->head;
	register size_t count = 0u;
	while (temp != NULL)
	{
		temp = temp->next;
		++count;
	}

	return count;
}

void stack_push(Stack * restrict stack, const void * restrict source)
{
	if (stack == NULL || source == NULL)
	{
		raise(SIGSEGV);
		return;
	}

	StackNode *temp = malloc(sizeof(StackNode));
	if (temp == NULL)
	{
		return;
	}

	temp->data = malloc(stack->size);
	if (temp->data == NULL)
	{
		free(temp);
		return;
	}

	memcpy(temp->data, source, stack->size);
	temp->next = stack->head;

	stack->head = temp;
}

void stack_top(const Stack * restrict stack, void * restrict dest)
{
	if (stack == NULL || dest == NULL)
	{
		raise(SIGSEGV);
		return;
	}

	if (stack->head == NULL)
	{
		raise(SIGSEGV);
		return;
	}

	memcpy(dest, stack->head->data, stack->size);
}

void stack_pop(Stack * restrict stack)
{
	if (stack == NULL)
	{
		raise(SIGSEGV);
		return;
	}

	if (stack->head == NULL)
	{
		raise(SIGSEGV);
		return;
	}

	register StackNode *temp = stack->head;

	stack->head = temp->next;

	free(temp->data);
	free(temp);
}