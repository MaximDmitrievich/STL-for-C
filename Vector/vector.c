#include <signal.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "vector.h"

struct vector
{
	void *data;
	size_t size, count;
};

struct vector_iterator
{
	Vector *vector;
	size_t pos;
};

Vector *vector_create(size_t count, size_t size)
{
	if (!size)
	{
		return NULL;
	}

	register Vector *vector = malloc(sizeof(Vector));
	if (vector == NULL)
	{
		return NULL;
	}

	if (count)
	{
		vector->data = calloc(count, size);
	}
	else
	{
		vector-> data = NULL;
	}

	vector->size = size;
	vector->count = count;

	return vector;
}

void vector_destroy(Vector * restrict vector)
{
	if (vector == NULL)
	{
		raise(SIGSEGV);
		return;
	}

	if (vector->data != NULL)
	{
		free(vector->data);
	}

	free(vector);
}

VectorIterator *vector_iterator_begin(const Vector * restrict vector)
{
	if (vector == NULL)
	{
		raise(SIGSEGV);
		return NULL;
	}

	VectorIterator *iterator = malloc(sizeof(VectorIterator));
	if (iterator == NULL)
	{
		return NULL;
	}

	iterator->vector = (Vector *) vector;
	if (vector->data == NULL && !vector->count)
	{
		iterator->pos = (size_t) -1;
	}
	else
	{
		iterator->pos = 0;
	}

	return iterator;
}

VectorIterator *vector_iterator_end(const Vector * restrict vector)
{
	if (vector == NULL)
	{
		raise(SIGSEGV);
		return NULL;
	}

	VectorIterator *iterator = malloc(sizeof(VectorIterator));
	if (iterator == NULL)
	{
		return NULL;
	}

	iterator->vector = (Vector *) vector;
	if (vector->data == NULL || !vector->count)
	{
		iterator->pos = (size_t) -1;
	}
	else
	{
		iterator->pos = vector->count - 1u;
	}

	return iterator;
}

void vector_iterator_destroy(VectorIterator * restrict iterator)
{
	if (iterator == NULL)
	{
		raise(SIGSEGV);
		return;
	}

	free(iterator);
}


void vector_iterator_prev(VectorIterator * restrict iterator)
{
	if (iterator == NULL)
	{
		raise(SIGSEGV);
		return;
	}

	if (iterator->vector->data == NULL || !iterator->vector->count)
	{
		raise(SIGSEGV);
		return;
	}

	if (iterator->pos == (size_t) -1)
	{
		raise(SIGSEGV);
		return;
	}

	if (!iterator->pos)
	{
		raise(SIGSEGV);
		return;
	}

	--iterator->pos;
}

void vector_iterator_next(VectorIterator * restrict iterator)
{
	if (iterator == NULL)
	{
		raise(SIGSEGV);
		return;
	}

	if (iterator->vector->data == NULL || !iterator->vector->count)
	{
		raise(SIGSEGV);
		return;
	}

	if (iterator->pos == (size_t) -1)
	{
		raise(SIGSEGV);
		return;
	}

	if (iterator->pos == iterator->vector->count - 1u)
	{
		raise(SIGSEGV);
		return;
	}

	++iterator->pos;
}

void vector_iterator_get(VectorIterator * restrict iterator, void * restrict dest, size_t cell_count)
{
	if (iterator == NULL || dest == NULL)
	{
		raise(SIGSEGV);
		return;
	}

	if (iterator->vector->data == NULL || !iterator->vector->count || iterator->pos == (size_t) -1 || iterator->vector->count < iterator->pos + cell_count)
	{
		raise(SIGSEGV);
		return;
	}

	memcpy(dest, (unsigned char *) iterator->vector->data + iterator->vector->size * iterator->pos, iterator->vector->size * cell_count);
}

void vector_iterator_set(VectorIterator * restrict iterator, void * restrict source, size_t cell_count)
{
	if (iterator == NULL || source == NULL)
	{
		raise(SIGSEGV);
		return;
	}

	if (iterator->vector->data == NULL || !iterator->vector->count || iterator->pos == (size_t) -1 || iterator->vector->count < iterator->pos + cell_count)
	{
		raise(SIGSEGV);
		return;
	}

	memcpy((unsigned char *) iterator->vector->data + iterator->vector->size * iterator->pos, source, iterator->vector->size * cell_count);
}

size_t vector_size(const Vector * restrict vector)
{
	if (vector == NULL)
	{
		raise(SIGSEGV);
		return (size_t) -1;
	}

	return vector->count;
}

void vector_resize(Vector * restrict vector, size_t cell_count)
{
	if (vector == NULL)
	{
		raise(SIGSEGV);
		return;
	}

	if (vector->size * cell_count / vector->size != cell_count)
	{
		raise(SIGFPE);
		return;
	}

	if (!cell_count)
	{
		if (vector->data == NULL && !vector->count)
		{
			return;
		}

		free(vector->data);
		vector->data = NULL;
		vector->count = 0u;
		return;
	}

	void *temp = realloc(vector->data, vector->size * cell_count);
	if (temp == NULL)
	{
		return;
	}

	vector->data = temp;
	if (cell_count > vector->count)
	{
		memset((unsigned char *) vector->data + vector->size * vector->count, '\0', vector->size * (cell_count - vector->count));
	}
	vector->count = cell_count;
}

bool vector_empty(const Vector * restrict vector)
{
	if (vector == NULL)
	{
		raise(SIGSEGV);
		return true;
	}

	return vector->data == NULL || !vector->count;
}

void vector_at_get(const Vector * restrict vector, size_t i, void * restrict dest, size_t cell_count)
{
	if (vector == NULL || dest == NULL)
	{
		raise(SIGSEGV);
		return;
	}

	if (vector->data == NULL || vector->count < i + cell_count)
	{
		raise(SIGSEGV);
		return;
	}

	if (!cell_count)
	{
		return;
	}
	memcpy(dest, (unsigned char *) vector->data + vector->size * i, vector->size * cell_count);
}

void vector_at_set(const Vector * restrict vector, size_t i, const void * restrict source, size_t cell_count)
{
	if (vector == NULL || source == NULL)
	{
		raise(SIGSEGV);
		return;
	}

	if (vector->data == NULL || vector->count < i + cell_count)
	{
		raise(SIGSEGV);
		return;
	}

	if (!cell_count)
	{
		return;
	}
	memcpy((unsigned char *) vector->data + vector->size * i, source, vector->size * cell_count);
}

void vector_front_get(const Vector * restrict vector, void * restrict dest, size_t cell_count)
{
	if (vector == NULL || dest == NULL)
	{
		raise(SIGSEGV);
		return;
	}

	if (vector->data == NULL || !vector->count || vector->count < cell_count)
	{
		raise(SIGSEGV);
		return;
	}

	if (!cell_count)
	{
		return;
	}
	memcpy(dest, vector->data, vector->size * cell_count);
}

void vector_front_set(const Vector * restrict vector, const void * restrict source, size_t cell_count)
{
	if (vector == NULL || source == NULL)
	{
		raise(SIGSEGV);
		return;
	}

	if (vector->data == NULL || !vector->count || vector->count < cell_count)
	{
		raise(SIGSEGV);
		return;
	}

	if (!cell_count)
	{
		return;
	}
	memcpy(vector->data, source, vector->size * cell_count);
}

void vector_back_get(const Vector * restrict vector, void * restrict dest, size_t cell_count)
{
	if (vector == NULL || dest == NULL)
	{
		raise(SIGSEGV);
		return;
	}

	if (vector->data == NULL || !vector->count || vector->count < cell_count)
	{
		raise(SIGSEGV);
		return;
	}

	if (!cell_count)
	{
		return;
	}
	memcpy(dest, (unsigned char *) vector->data + vector->size * (vector->count - cell_count), vector->size * cell_count);
}

void vector_back_set(const Vector * restrict vector, const void * restrict source, size_t cell_count)
{
	if (vector == NULL || source == NULL)
	{
		raise(SIGSEGV);
		return;
	}

	if (vector->data == NULL || !vector->count || vector->count < cell_count)
	{
		raise(SIGSEGV);
		return;
	}

	if (!cell_count)
	{
		return;
	}
	memcpy((unsigned char *) vector->data + vector->size * (vector->count - cell_count), source, vector->size * cell_count);
}

void *vector_data(const Vector * restrict vector)
{
	if (vector == NULL)
	{
		raise(SIGSEGV);
		return NULL;
	}

	return vector->data;
}

void vector_push_back(Vector * restrict vector, const void * restrict source, size_t cell_count)
{
	if (vector == NULL || source == NULL)
	{
		raise(SIGSEGV);
		return;
	}

	if (!cell_count)
	{
		return;
	}

	if (vector->size * (cell_count + vector->count) / vector->size != cell_count + vector->count)
	{
		raise(SIGFPE);
		return;
	}

	void *temp = realloc(vector->data, vector->size * (vector->count + cell_count));
	if (temp == NULL)
	{
		return;
	}

	vector->data = temp;
	memcpy((unsigned char *) vector->data + vector->size * vector->count, source, vector->size * cell_count);
	vector->count += cell_count;
}

void vector_pop_back(Vector * restrict vector, size_t cell_count)
{
	if (vector == NULL)
	{
		raise(SIGSEGV);
		return;
	}

	if (vector->count < cell_count)
	{
		raise(SIGSEGV);
		return;
	}

	if (!cell_count)
	{
		return;
	}

	if (vector->count == cell_count)
	{
		free(vector->data);
		vector->data = NULL;
		vector->count = 0u;
		return;
	}

	void *temp = realloc(vector->data, vector->size * (vector->count - cell_count));
	if (temp == NULL)
	{
		return;
	}

	vector->data = temp;
	vector->count -= cell_count;
}

void vector_iterator_insert(VectorIterator * restrict iterator, const void * source, size_t cell_count)
{
	if (iterator == NULL || source == NULL)
	{
		raise(SIGSEGV);
		return;
	}

	if (iterator->vector->data == NULL || !iterator->vector->count || iterator->pos == (size_t) -1)
	{
		raise(SIGSEGV);
		return;
	}

	if (!cell_count)
	{
		return;
	}

	void *temp = realloc(iterator->vector->data, iterator->vector->count + cell_count);
	if (temp == NULL)
	{
		return;
	}

	iterator->vector->data = temp;
	memmove((unsigned char *) iterator->vector->data + iterator->vector->size * (iterator->pos + cell_count), (unsigned char *) iterator->vector->data + iterator->vector->size * iterator->pos, iterator->vector->count - iterator->pos);
	memcpy((unsigned char *) iterator->vector->data + iterator->vector->size * iterator->pos, source, iterator->vector->size * cell_count);
}

void vector_iterator_erase(VectorIterator * restrict iterator, size_t cell_count)
{
	if (iterator == NULL)
	{
		raise(SIGSEGV);
		return;
	}

	if (iterator->vector->data == NULL || !iterator->vector->count || iterator->pos == (size_t) -1)
	{
		raise(SIGSEGV);
		return;
	}

	if (iterator->vector->count - iterator->pos < cell_count)
	{
		raise(SIGSEGV);
		return;
	}

	if (!cell_count)
	{
		return;
	}

	if (iterator->pos + cell_count == iterator->vector->count)
	{
		if (!iterator->pos)
		{
			free(iterator->vector->data);
			iterator->vector->data = NULL;
			iterator->vector->count = 0u;
			iterator->pos = (size_t) -1;
			return;
		}

		void *temp = realloc(iterator->vector->data, iterator->vector->count - cell_count);
		if (temp == NULL)
		{
			return;
		}

		iterator->vector->data = temp;
		iterator->vector->count -= cell_count;
		--iterator->pos;
		return;
	}

	memmove((unsigned char *) iterator->vector->data + iterator->vector->size * iterator->pos, (unsigned char *) iterator->vector->data + iterator->vector->size * (iterator->pos + cell_count), iterator->vector->size * cell_count);
	iterator->vector->count -= cell_count;
	if (!iterator->pos)
	{
		iterator->pos += iterator->vector->size * cell_count;
	}
	void *temp = realloc(iterator->vector->data, iterator->vector->count - cell_count);
	if (temp == NULL)
	{
		return;
	}

	iterator->vector->data = temp;
}

void vector_sort(const Vector * restrict vector, int (*compar)(const void *, const void *))
{
	if (vector == NULL || compar == NULL)
	{
		raise(SIGSEGV);
		return;
	}

	if (vector->data == NULL || !vector->count)
	{
		return;
	}

	qsort(vector->data, vector->count, vector->size, compar);
}

void vector_clear(Vector * restrict vector)
{
	if (vector == NULL)
	{
		raise(SIGSEGV);
		return;
	}

	if (vector->data != NULL || vector->count)
	{
		free(vector->data);
		vector->data = NULL;
		vector->count = 0u;
	}
}