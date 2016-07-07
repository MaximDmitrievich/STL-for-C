#include <stdbool.h>
#include <stdio.h>
#include "vector.h"

int main(void)
{
	size_t n = 10;
	Vector *vector = vector_create(n, sizeof(long double));

	long double temp = 0.0l;
	for (size_t i = 0u; i < n; ++i)
	{
		scanf("%Lf", &temp);
		vector_at_set(vector, i, &temp, 1u);
	}

	putchar('\n');
//	vector_resize(vector, n + 20);

	for (size_t i = 0u; i < vector_size(vector); ++i)
	{
		vector_at_get(vector, i, &temp, 1u);
		printf("%Lf\n", temp);
	}

	vector_destroy(vector);
	vector = NULL;
	return 0;
}