#include <signal.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"

typedef struct queue_node QueueNode;

struct queue_node
{
	void *data;
	QueueNode *next;
};

struct queue
{
	size_t size;
	QueueNode *head;
	QueueNode *tail;
};

Queue *queue_create(size_t size)
{
	if (!size)
	{
		return NULL;
	}

	register Queue *queue = malloc(sizeof(Queue));
	if (queue == NULL)
	{
		return NULL;
	}

	queue->size = size;
	queue->head = queue->tail = NULL;

	return queue;
}

void queue_destroy(Queue * restrict queue)
{
	if (queue == NULL)
	{
		raise(SIGSEGV);
		return;
	}

	register QueueNode *temp = queue->head;
	while (temp != NULL)
	{
		QueueNode *local_temp = temp->next;

		free(temp->data);
		free(temp);

		temp = local_temp;
	}

	free(queue);
}

void queue_clear(Queue * restrict queue)
{
	if (queue == NULL)
	{
		raise(SIGSEGV);
		return;
	}

	register QueueNode *temp = queue->head;
	queue->head = queue->tail = NULL;
	while (temp != NULL)
	{
		QueueNode *local_temp = temp->next;

		free(temp->data);
		free(temp);

		temp = local_temp;
	}
}

bool queue_empty(const Queue * restrict queue)
{
	if (queue == NULL)
	{
		raise(SIGSEGV);
		return true;
	}

	return queue->head == NULL;
}

size_t queue_size(const Queue * restrict queue)
{
	if (queue == NULL)
	{
		raise(SIGSEGV);
		return (size_t) -1;
	}

	register QueueNode *temp = queue->head;
	register size_t count = 0u;
	while (temp != NULL)
	{
		temp = temp->next;
		++count;
	}

	return count;
}

void queue_push(Queue * restrict queue, const void * restrict source)
{
	if (queue == NULL || source == NULL)
	{
		raise(SIGSEGV);
		return;
	}

	register QueueNode *temp = malloc(sizeof(QueueNode));
	if (temp == NULL)
	{
		return;
	}

	temp->data = malloc(queue->size);
	if (temp->data == NULL)
	{
		free(temp);
		return;
	}

	memcpy(temp->data, source, queue->size);
	temp->next = NULL;

	if (queue->head == NULL)
	{
		queue->head = temp;
	}
	else
	{
		queue->tail->next = temp;
	}
	queue->tail = temp;
}

void queue_front(const Queue * restrict queue, void * restrict dest)
{
	if (queue == NULL || dest == NULL)
	{
		raise(SIGSEGV);
		return;
	}

	if (queue->head == NULL)
	{
		raise(SIGSEGV);
		return;
	}

	memcpy(dest, queue->head->data, queue->size);
}

void queue_pop(Queue * restrict queue)
{
	if (queue == NULL)
	{
		raise(SIGSEGV);
		return;
	}

	if (queue->head == NULL)
	{
		raise(SIGSEGV);
		return;
	}

	register QueueNode *temp = queue->head;

	queue->head = temp->next;

	if (temp->next == NULL)
	{
		queue->tail = NULL;
	}

	free(temp->data);
	free(temp);
}