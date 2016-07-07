#include <stdbool.h>
#include <stdio.h>
#include "deque.h"

int main(void)
{
	Deque *q1 = deque_create(sizeof(int));

	int temp = 0;
	while (scanf("%d", &temp) != EOF)
	{
		deque_push_front(q1, &temp);
		deque_push_back(q1, &temp);
	}

	putchar('\n');

	while (!deque_empty(q1))
	{
		deque_front(q1, &temp);
		printf("%d\t", temp);
		deque_pop_front(q1);
	}

	deque_destroy(q1);
	q1 = NULL;
	return 0;
}