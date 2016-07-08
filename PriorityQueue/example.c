#include <stdbool.h>
#include <stdio.h>
#include "priority_queue.h"

int compar(const void *, const void *);

int main(void)
{
	PriorityQueue *q1 = priority_queue_create(sizeof(int), compar);

	int temp = 0;
	while (scanf("%d", &temp) != EOF)
	{
		priority_queue_push(q1, &temp);
	}

	while (!priority_queue_empty(q1))
	{
		priority_queue_front(q1, &temp);
		printf("%d\n", temp);
		priority_queue_pop(q1);
	}

	putchar('\n');

	priority_queue_destroy(q1);
	q1 = NULL;
	return 0;
}

int compar(const void *value_1, const void *value_2)
{
	if (*(int *) value_1 > *(int *) value_2)
	{
		return 1;
	}
	else if (*(int *) value_1 < *(int *) value_2)
	{
		return -1;
	}
	else
	{
		return 0;
	}
}