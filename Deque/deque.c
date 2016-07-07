#include <signal.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "deque.h"

typedef struct deque_node DequeNode;

struct deque_node
{
	void *data;
	DequeNode *prev;
	DequeNode *next;
};

struct deque
{
	size_t size;
	DequeNode *head;
	DequeNode *tail;
};

Deque *deque_create(size_t size)
{
	if (!size)
	{
		return NULL;
	}

	register Deque *deque = malloc(sizeof(Deque));
	if (deque == NULL)
	{
		return NULL;
	}

	deque->size = size;
	deque->head = deque->tail = NULL;

	return deque;
}

void deque_destroy(Deque * restrict deque)
{
	if (deque == NULL)
	{
		raise(SIGSEGV);
		return;
	}

	register DequeNode *temp = deque->head;
	while (temp != NULL)
	{
		DequeNode *local_temp = temp->next;

		free(temp->data);
		free(temp);

		temp = local_temp;
	}

	free(deque);
}

void deque_clear(Deque * restrict deque)
{
	if (deque == NULL)
	{
		raise(SIGSEGV);
		return;
	}

	register DequeNode *temp = deque->head;
	deque->head = deque->tail = NULL;
	while (temp != NULL)
	{
		DequeNode *local_temp = temp->next;

		free(temp->data);
		free(temp);

		temp = local_temp;
	}
}

bool deque_empty(const Deque * restrict deque)
{
	if (deque == NULL)
	{
		raise(SIGSEGV);
		return true;
	}

	return deque->head == NULL;
}

size_t deque_size(const Deque * restrict deque)
{
	if (deque == NULL)
	{
		raise(SIGSEGV);
		return (size_t) -1;
	}

	register DequeNode *temp = deque->head;
	register size_t count = 0u;
	while (temp != NULL)
	{
		temp = temp->next;
		++count;
	}

	return count;
}

void deque_push_front(Deque * restrict deque, const void * restrict source)
{
	if (deque == NULL || source == NULL)
	{
		raise(SIGSEGV);
		return;
	}

	register DequeNode *temp = malloc(sizeof(DequeNode));
	if (temp == NULL)
	{
		return;
	}

	temp->data = malloc(deque->size);
	if (temp->data == NULL)
	{
		free(temp);
		return;
	}

	memcpy(temp->data, source, deque->size);
	temp->prev = NULL;
	temp->next = deque->head;

	deque->head = temp;
	if (deque->tail == NULL)
	{
		deque->tail = temp;
	}
	else
	{
		temp->next->prev = temp;
	}
}

void deque_push_back(Deque * restrict deque, const void * restrict source)
{
	if (deque == NULL || source == NULL)
	{
		raise(SIGSEGV);
		return;
	}

	register DequeNode *temp = malloc(sizeof(DequeNode));
	if (temp == NULL)
	{
		return;
	}

	temp->data = malloc(deque->size);
	if (temp->data == NULL)
	{
		free(temp);
		return;
	}

	memcpy(temp->data, source, deque->size);
	temp->prev = deque->tail;
	temp->next = NULL;

	if (deque->head == NULL)
	{
		deque->head = temp;
	}
	else
	{
		deque->tail->next = temp;
	}
	deque->tail = temp;
}

void deque_front(const Deque * restrict deque, void * restrict dest)
{
	if (deque == NULL || dest == NULL)
	{
		raise(SIGSEGV);
		return;
	}

	if (deque->head == NULL)
	{
		raise(SIGSEGV);
		return;
	}

	memcpy(dest, deque->head->data, deque->size);
}

void deque_back(const Deque * restrict deque, void * restrict dest)
{
	if (deque == NULL || dest == NULL)
	{
		raise(SIGSEGV);
		return;
	}

	if (deque->tail == NULL)
	{
		raise(SIGSEGV);
		return;
	}

	memcpy(dest, deque->tail->data, deque->size);
}

void deque_pop_front(Deque * restrict deque)
{
	if (deque == NULL)
	{
		raise(SIGSEGV);
		return;
	}

	if (deque->head == NULL)
	{
		raise(SIGSEGV);
		return;
	}

	register DequeNode *temp = deque->head;

	deque->head = temp->next;
	if (temp->next == NULL)
	{
		deque->tail = NULL;
	}
	else
	{
		temp->next->prev = NULL;
	}

	free(temp->data);
	free(temp);
}

void deque_pop_back(Deque * restrict deque)
{
	if (deque == NULL)
	{
		raise(SIGSEGV);
		return;
	}

	if (deque->tail == NULL)
	{
		raise(SIGSEGV);
		return;
	}

	register DequeNode *temp = deque->tail;

	if (temp->prev == NULL)
	{
		deque->head = NULL;
	}
	else
	{
		temp->prev->next = NULL;
	}
	deque->tail = temp->prev;

	free(temp->data);
	free(temp);
}