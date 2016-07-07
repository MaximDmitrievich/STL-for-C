#include <stdbool.h>
#include <stdio.h>
#include "queue.h"

int main(void)
{
	Queue *q1 = queue_create(sizeof(int));

	int temp = 0;
	while (scanf("%d", &temp) != EOF)
	{
		queue_push(q1, &temp);
	}

	putchar('\n');

	while (!queue_empty(q1))
	{
		queue_front(q1, &temp);
		printf("%d\t", temp);
		queue_pop(q1);
	}

	queue_destroy(q1);
	q1 = NULL;
	return 0;
}