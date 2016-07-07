#include <stdbool.h>
#include <stdio.h>
#include "list.h"

int main(void)
{
	List *list = list_create(sizeof(int));

	int temp = 0;
	while (scanf("%d", &temp) != EOF)
	{
		list_push_back(list, &temp);
	}
	list_reverse(list);

	putchar('\n');

	ListIterator *it = list_iterator_begin(list);
	while (list_iterator_dereferenceable(it))
	{
		list_iterator_get(it, &temp);
		printf("%d\n", temp);
		list_iterator_next(it);
	}
	list_iterator_destroy(it);

	putchar('\n');
	list_clear(list);

	it = list_iterator_end(list);
	while (list_iterator_dereferenceable(it))
	{
		list_iterator_get(it, &temp);
		printf("%d\n", temp);
		list_iterator_prev(it);
	}
	list_iterator_destroy(it);

	it = NULL;
	list_destroy(list);
	list = NULL;

	return 0;
}