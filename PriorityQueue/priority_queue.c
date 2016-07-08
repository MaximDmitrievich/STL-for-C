#include <signal.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "priority_queue.h"

#define HEAP_SIZE 256u

struct priority_queue
{
	void *data;
	size_t size;
	size_t capacity;
	size_t count;
	int (*compar)(const void *, const void *);
};

PriorityQueue *priority_queue_create(size_t size, int (*compar)(const void *, const void *))
{
	if (!size || compar == NULL)
	{
		return NULL;
	}

	if (size * HEAP_SIZE / size != HEAP_SIZE)
	{
		raise(SIGFPE);
		return NULL;
	}

	register PriorityQueue *priority_queue = malloc(sizeof(PriorityQueue));
	if (priority_queue == NULL)
	{
		return NULL;
	}

	priority_queue->data = malloc(size * HEAP_SIZE);
	if (priority_queue->data == NULL)
	{
		free(priority_queue);
		return NULL;
	}

	priority_queue->size = size;
	priority_queue->capacity = HEAP_SIZE;
	priority_queue->count = 0u;
	priority_queue->compar = compar;

	return priority_queue;
}

void priority_queue_destroy(PriorityQueue * restrict priority_queue)
{
	if (priority_queue == NULL)
	{
		raise(SIGSEGV);
		return;
	}

	free(priority_queue->data);
	free(priority_queue);
}

void priority_queue_clear(PriorityQueue * restrict priority_queue)
{
	if (priority_queue == NULL)
	{
		raise(SIGSEGV);
		return;
	}

	void *temp = realloc(priority_queue->data, priority_queue->size * HEAP_SIZE);
	if (temp == NULL)
	{
		return;
	}

	priority_queue->data = temp;
	priority_queue->capacity = HEAP_SIZE;
	priority_queue->count = 0u;
}

bool priority_queue_empty(const PriorityQueue * restrict priority_queue)
{
	if (priority_queue == NULL)
	{
		raise(SIGSEGV);
		return true;
	}

	return !priority_queue->count;
}

size_t priority_queue_size(const PriorityQueue * restrict priority_queue)
{
	if (priority_queue == NULL)
	{
		raise(SIGSEGV);
		return (size_t) -1;
	}

	return priority_queue->count;
}

void priority_queue_push(PriorityQueue * restrict priority_queue, const void * restrict source)
{
	if (priority_queue == NULL || source == NULL)
	{
		raise(SIGSEGV);
		return;
	}

	if (priority_queue->count + 1u >= priority_queue->capacity)
	{
		if (priority_queue->capacity * 2u / priority_queue->capacity != 2u)
		{
			raise(SIGFPE);
			return;
		}

		void *temp = realloc(priority_queue->data, priority_queue->size * priority_queue->capacity * 2u);
		if (temp == NULL)
		{
			return;
		}

		priority_queue->data = temp;
		priority_queue->capacity *= 2u;
	}

	memcpy((unsigned char *) priority_queue->data + priority_queue->size * priority_queue->count, source, priority_queue->size);
	++priority_queue->count;

	size_t temp = priority_queue->count - 1u;
	while (temp)
	{
		size_t local_temp = 0u;
		if (temp % 2u)
		{
			local_temp = (temp - 1u) / 2u;
		}
		else
		{
			local_temp = (temp - 2u) / 2u;
		}

		if (priority_queue->compar((unsigned char *) priority_queue->data + priority_queue->size * temp, (unsigned char *) priority_queue->data + priority_queue->size * local_temp) > 0)
		{
			memcpy((unsigned char *) priority_queue->data + priority_queue->size * (priority_queue->capacity - 1u), (unsigned char *) priority_queue->data + priority_queue->size * temp, priority_queue->size);
			memcpy((unsigned char *) priority_queue->data + priority_queue->size * temp, (unsigned char *) priority_queue->data + priority_queue->size * local_temp, priority_queue->size);
			memcpy((unsigned char *) priority_queue->data + priority_queue->size * local_temp, (unsigned char *) priority_queue->data + priority_queue->size * (priority_queue->capacity - 1u), priority_queue->size);
		}
		temp = local_temp;
	}
}

void priority_queue_front(const PriorityQueue * restrict priority_queue, void * restrict dest)
{
	if (priority_queue == NULL || dest == NULL)
	{
		raise(SIGSEGV);
		return;
	}

	if (!priority_queue->count)
	{
		raise(SIGSEGV);
		return;
	}

	memcpy(dest, priority_queue->data, priority_queue->size);
}

void priority_queue_pop(PriorityQueue * restrict priority_queue)
{
	if (priority_queue == NULL)
	{
		raise(SIGSEGV);
		return;
	}

	if (!priority_queue->count)
	{
		raise(SIGSEGV);
		return;
	}

	if (priority_queue->capacity / 2u >= priority_queue->count && priority_queue->capacity > HEAP_SIZE)
	{
		void *temp = realloc(priority_queue->data, priority_queue->size * priority_queue->capacity / 2u);
		if (temp == NULL)
		{
			return;
		}

		priority_queue->data = temp;
		priority_queue->capacity /= 2u;
	}

	--priority_queue->count;
	memcpy(priority_queue->data, (unsigned char *) priority_queue->data + priority_queue->size * priority_queue->count, priority_queue->size);

	size_t temp = 0;
	while (temp * 2u + 2u < priority_queue->count)
	{
		size_t local_temp = 0u;
		if (priority_queue->compar((unsigned char *) priority_queue->data + (temp * 2u + 1u) * priority_queue->size, (unsigned char *) priority_queue->data + (temp * 2u + 2u) * priority_queue->size) >= 0)
		{
			local_temp = temp * 2u + 1;
		}
		else
		{
			local_temp = temp * 2u + 2u;
		}

		if (priority_queue->compar((unsigned char *) priority_queue->data + priority_queue->size * temp, (unsigned char *) priority_queue->data + priority_queue->size * local_temp) < 0)
		{
			memcpy((unsigned char *) priority_queue->data + priority_queue->size * (priority_queue->capacity - 1u), (unsigned char *) priority_queue->data + priority_queue->size * temp, priority_queue->size);
			memcpy((unsigned char *) priority_queue->data + priority_queue->size * temp, (unsigned char *) priority_queue->data + priority_queue->size * local_temp, priority_queue->size);
			memcpy((unsigned char *) priority_queue->data + priority_queue->size * local_temp, (unsigned char *) priority_queue->data + priority_queue->size * (priority_queue->capacity - 1u), priority_queue->size);
		}
		temp = local_temp;
	}
}