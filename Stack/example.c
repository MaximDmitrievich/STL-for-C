#include <stdbool.h>
#include <stdio.h>
#include "stack.h"

int main(void)
{
	Stack *s1 = stack_create(sizeof(int));

	int temp = 0;
	while (scanf("%d", &temp) != EOF)
	{
		stack_push(s1, &temp);
	}

	putchar('\n');

	while (!stack_empty(s1))
	{
		stack_top(s1, &temp);
		printf("%d\t", temp);

		stack_pop(s1);
	}

	stack_destroy(s1);
	s1 = NULL;
	return 0;
}