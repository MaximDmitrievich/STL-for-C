#include <signal.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

typedef struct list_node ListNode;

struct list_node
{
	void *data;
	ListNode *prev;
	ListNode *next;
};

struct list
{
	size_t size;
	ListNode *head;
	ListNode *tail;
};

struct list_iterator
{
	List *list;
	bool origin;
	ListNode *node;
};

List *list_create(size_t size)
{
	if (!size)
	{
		return NULL;
	}

	register List *list = malloc(sizeof(List));
	if (list == NULL)
	{
		return NULL;
	}

	list->size = size;
	list->head = list->tail = NULL;

	return list;
}

void list_destroy(List * restrict list)
{
	if (list == NULL)
	{
		raise(SIGSEGV);
		return;
	}

	register ListNode *temp = list->head;
	while (temp != NULL)
	{
		ListNode *local_temp = temp->next;

		free(temp->data);
		free(temp);

		temp = local_temp;
	}

	free(list);
}

bool list_empty(const List * restrict list)
{
	if (list == NULL)
	{
		raise(SIGSEGV);
		return true;
	}

	return list->head == NULL || list->tail == NULL;
}

size_t list_size(const List * restrict list)
{
	if (list == NULL)
	{
		raise(SIGSEGV);
		return (size_t) -1;
	}

	register ListNode *temp = list->head;
	register size_t count = 0u;
	while (temp != NULL)
	{
		temp = temp->next;
		++count;
	}

	return count;
}

void list_push_front(List * restrict list, const void * restrict source)
{
	if (list == NULL || source == NULL)
	{
		raise(SIGSEGV);
		return;
	}

	register ListNode *temp = malloc(sizeof(ListNode));
	if (temp == NULL)
	{
		return;
	}

	temp->data = malloc(list->size);
	if (temp->data == NULL)
	{
		free(temp);
		return;
	}

	memcpy(temp->data, source, list->size);
	temp->prev = NULL;
	temp->next = list->head;

	list->head = temp;
	if (list->tail == NULL)
	{
		list->tail = temp;
	}
	else
	{
		temp->next->prev = temp;
	}
}

void list_push_back(List * restrict list, const void * restrict source)
{
	if (list == NULL || source == NULL)
	{
		raise(SIGSEGV);
		return;
	}

	register ListNode *temp = malloc(sizeof(ListNode));
	if (temp == NULL)
	{
		return;
	}

	temp->data = malloc(list->size);
	if (temp->data == NULL)
	{
		free(temp);
		return;
	}

	memcpy(temp->data, source, list->size);
	temp->prev = list->tail;
	temp->next = NULL;

	if (list->head == NULL)
	{
		list->head = temp;
	}
	else
	{
		list->tail->next = temp;
	}
	list->tail = temp;
}

void list_front(const List * restrict list, void * restrict dest)
{
	if (list == NULL || dest == NULL)
	{
		raise(SIGSEGV);
		return;
	}

	if (list->head == NULL)
	{
		raise(SIGSEGV);
		return;
	}

	memcpy(dest, list->head->data, list->size);
}

void list_back(const List * restrict list, void * restrict dest)
{
	if (list == NULL || dest == NULL)
	{
		raise(SIGSEGV);
		return;
	}

	if (list->tail == NULL)
	{
		raise(SIGSEGV);
		return;
	}

	memcpy(dest, list->tail->data, list->size);
}

void list_pop_front(List * restrict list)
{
	if (list == NULL)
	{
		raise(SIGSEGV);
		return;
	}

	if (list->head == NULL)
	{
		raise(SIGSEGV);
		return;
	}

	register ListNode *temp = list->head;

	list->head = temp->next;
	if (temp->next == NULL)
	{
		list->tail = NULL;
	}
	else
	{
		temp->next->prev = NULL;
	}

	free(temp->data);
	free(temp);
}

void list_pop_back(List * restrict list)
{
	if (list == NULL)
	{
		raise(SIGSEGV);
		return;
	}

	if (list->tail == NULL)
	{
		raise(SIGSEGV);
		return;
	}

	register ListNode *temp = list->tail;

	if (temp->prev == NULL)
	{
		list->head = NULL;
	}
	else
	{
		temp->prev->next = NULL;
	}
	list->tail = temp->prev;

	free(temp->data);
	free(temp);
}

void list_remove(List * restrict list, void * restrict value)
{
	if (list == NULL || value == NULL)
	{
		raise(SIGSEGV);
		return;
	}

	register ListNode *temp = list->head;
	while (temp != NULL)
	{
		if (!memcmp(value, temp->data, list->size))
		{
			if (list->head == list->tail)
			{
				list->head = list->tail = NULL;
			}
			else
			{
				if (temp->prev != NULL)
				{
					temp->prev->next = temp->next;
				}
				else
				{
					list->head = temp->next;
				}
				if (temp->next != NULL)
				{
					temp->next->prev = temp->prev;
				}
				else
				{
					list->tail = temp->prev;
				}
			}

			free(temp->data);
			free(temp);
			return;
		}

		temp = temp->next;
	}
}

void list_reverse(List * restrict list)
{
	if (list == NULL)
	{
		raise(SIGSEGV);
		return;
	}

	register ListNode *temp = list->head;
	list->head = list->tail;
	list->tail = temp;
	while (temp != NULL)
	{
		ListNode *local_temp = temp->next;
		temp->next = temp->prev;
		temp->prev = local_temp;
		temp = local_temp;
	}
}

void list_clear(List * restrict list)
{
	if (list == NULL)
	{
		raise(SIGSEGV);
		return;
	}

	register ListNode *temp = list->head;
	list->head = list->tail = NULL;
	while (temp != NULL)
	{
		ListNode *local_temp = temp->next;

		free(temp->data);
		free(temp);

		temp = local_temp;
	}
}

ListIterator *list_iterator_begin(const List * restrict list)
{
	if (list == NULL)
	{
		raise(SIGSEGV);
		return NULL;
	}

	register ListIterator *iterator = malloc(sizeof(ListIterator));
	if (list == NULL)
	{
		return NULL;
	}

	iterator->list = (List *) list;
	iterator->origin = true;
	iterator->node = list->head;

	return iterator;
}

ListIterator *list_iterator_end(const List * restrict list)
{
	if (list == NULL)
	{
		raise(SIGSEGV);
		return NULL;
	}

	register ListIterator *iterator = malloc(sizeof(ListIterator));
	if (list == NULL)
	{
		return NULL;
	}

	iterator->list = (List *) list;
	iterator->origin = false;
	iterator->node = list->tail;

	return iterator;
}

void list_iterator_destroy(ListIterator * restrict iterator)
{
	if (iterator == NULL)
	{
		raise(SIGSEGV);
		return;
	}

	free(iterator);
}

bool list_iterator_equal(const ListIterator * restrict iterator1, const ListIterator * restrict iterator2)
{
	if (iterator1 == NULL || iterator2 == NULL)
	{
		raise(SIGSEGV);
		return false;
	}

	return iterator1->list == iterator2->list && iterator1->node == iterator2->node && (iterator1->node != NULL || iterator2->node != NULL || iterator1->origin == iterator2->origin);
}

bool list_iterator_inequal(const ListIterator * restrict iterator1, const ListIterator * restrict iterator2)
{
	if (iterator1 == NULL || iterator2 == NULL)
	{
		raise(SIGSEGV);
		return true;
	}

	return iterator1->list != iterator2->list || iterator1->node != iterator2->node || (iterator1->node == NULL && iterator2->node == NULL && iterator1->origin != iterator2->origin);
}

bool list_iterator_dereferenceable(const ListIterator * restrict iterator)
{
	if (iterator == NULL)
	{
		raise(SIGSEGV);
		return false;
	}

	return iterator->node != NULL;
}

void list_iterator_insert_front(ListIterator * restrict iterator, const void * restrict source)
{
	if (iterator == NULL || source == NULL)
	{
		raise(SIGSEGV);
		return;
	}

	register ListNode *temp = malloc(sizeof(ListNode));
	if (temp == NULL)
	{
		return;
	}

	temp->data = malloc(iterator->list->size);
	if (temp->data == NULL)
	{
		free(temp);
		return;
	}

	memcpy(temp->data, source, iterator->list->size);
	if (iterator->node == NULL && iterator->origin)
	{
		temp->prev = NULL;
		temp->next = iterator->list->head;
		if (iterator->list->head != NULL)
		{
			iterator->list->head->prev = temp;
		}
		iterator->list->head = temp;
		if (iterator->list->tail == NULL)
		{
			iterator->list->tail = temp;
		}
	}
	else if (iterator->node == NULL && !iterator->origin)
	{
		temp->prev = iterator->list->tail;
		temp->next = NULL;
		if (iterator->list->tail != NULL)
		{
			iterator->list->tail->next = temp;
		}
		if (iterator->list->head == NULL)
		{
			iterator->list->head = temp;
		}
		iterator->list->tail = temp;
	}
	else
	{
		temp->prev = iterator->node->prev;
		temp->next = iterator->node;
		if (temp->prev == NULL)
		{
			iterator->list->head = temp;
		}
		else
		{
			iterator->node->prev->next = temp;
		}
		iterator->node->prev = temp;
	}

	iterator->node = temp;
}

void list_iterator_insert_back(ListIterator * restrict iterator, const void * restrict source)
{
	if (iterator == NULL || source == NULL)
	{
		raise(SIGSEGV);
		return;
	}

	register ListNode *temp = malloc(sizeof(ListNode));
	if (temp == NULL)
	{
		return;
	}

	temp->data = malloc(iterator->list->size);
	if (temp->data == NULL)
	{
		free(temp);
		return;
	}

	memcpy(temp->data, source, iterator->list->size);
	if (iterator->node == NULL && iterator->origin)
	{
		temp->prev = NULL;
		temp->next = iterator->list->head;
		if (iterator->list->head != NULL)
		{
			iterator->list->head->prev = temp;
		}
		iterator->list->head = temp;
		if (iterator->list->tail == NULL)
		{
			iterator->list->tail = temp;
		}
	}
	else if (iterator->node == NULL && !iterator->origin)
	{
		temp->prev = iterator->list->tail;
		temp->next = NULL;
		if (iterator->list->tail != NULL)
		{
			iterator->list->tail->next = temp;
		}
		if (iterator->list->head == NULL)
		{
			iterator->list->head = temp;
		}
		iterator->list->tail = temp;
	}
	else
	{
		temp->prev = iterator->node;
		temp->next = iterator->node->next;
		if (temp->next == NULL)
		{
			iterator->list->tail = temp;
		}
		else
		{
			iterator->node->next->prev = temp;
		}
		iterator->node->next = temp;
	}

	iterator->node = temp;
}

void list_iterator_erase(ListIterator * restrict iterator)
{
	if (iterator == NULL)
	{
		raise(SIGSEGV);
		return;
	}

	if (iterator->node == NULL)
	{
		raise(SIGSEGV);
		return;
	}

	register ListNode *temp = iterator->node;

	if (iterator->list->head == iterator->list->tail)
	{
		iterator->list->head = iterator->list->tail = NULL;
		iterator->node = NULL;
	}
	else
	{
		if (iterator->node->prev != NULL)
		{
			iterator->node->prev->next = iterator->node->next;
		}
		else
		{
			iterator->list->head = iterator->node->next;
		}
		if (iterator->node->next != NULL)
		{
			iterator->node->next->prev = iterator->node->prev;
		}
		else
		{
			iterator->list->tail = iterator->node->prev;
		}

		if (iterator->origin)
		{
			iterator->node = iterator->node->next;
		}
		else
		{
			iterator->node = iterator->node->prev;
		}
	}

	free(temp->data);
	free(temp);
}

void list_iterator_get(ListIterator * restrict iterator, void * restrict dest)
{
	if (iterator == NULL || dest == NULL)
	{
		raise(SIGSEGV);
		return;
	}

	if (iterator->node == NULL)
	{
		raise(SIGSEGV);
		return;
	}

	memcpy(dest, iterator->node->data, iterator->list->size);
}

void list_iterator_set(ListIterator * restrict iterator, void * restrict source)
{
	if (iterator == NULL || source == NULL)
	{
		raise(SIGSEGV);
		return;
	}

	if (iterator->node == NULL)
	{
		raise(SIGSEGV);
		return;
	}

	memcpy(iterator->node->data, source, iterator->list->size);
}

void list_iterator_prev(ListIterator * restrict iterator)
{
	if (iterator == NULL)
	{
		raise(SIGSEGV);
		return;
	}

	if (iterator->list->head == NULL || iterator->list->tail == NULL)
	{
		raise(SIGSEGV);
		return;
	}

	if (iterator->node == NULL && iterator->origin)
	{
		raise(SIGSEGV);
		return;
	}

	if (iterator->node == NULL)
	{
		iterator->node = iterator->list->tail;
		return;
	}

	iterator->origin = true;
	iterator->node = iterator->node->prev;
}

void list_iterator_next(ListIterator * restrict iterator)
{
	if (iterator == NULL)
	{
		raise(SIGSEGV);
		return;
	}

	if (iterator->list->head == NULL || iterator->list->tail == NULL)
	{
		raise(SIGSEGV);
		return;
	}

	if (iterator->node == NULL && !iterator->origin)
	{
		raise(SIGSEGV);
		return;
	}

	if (iterator->node == NULL)
	{
		iterator->node = iterator->list->head;
		return;
	}

	iterator->origin = false;
	iterator->node = iterator->node->next;
}