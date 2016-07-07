#ifndef _VECTOR_H_
#define _VECTOR_H_

typedef struct vector Vector;

typedef struct vector_iterator VectorIterator;

Vector *vector_create(size_t count, size_t size);

void vector_destroy(Vector * restrict vector);

VectorIterator *vector_iterator_begin(const Vector * restrict vector);

VectorIterator *vector_iterator_end(const Vector * restrict vector);

void vector_iterator_prev(VectorIterator * restrict iterator);

void vector_iterator_next(VectorIterator * restrict iterator);

void vector_iterator_get(VectorIterator * restrict iterator, void * restrict dest, size_t cell_count);

void vector_iterator_set(VectorIterator * restrict iterator, void * restrict source, size_t cell_count);

size_t vector_size(const Vector * restrict vector);

void vector_resize(Vector * restrict vector, size_t cell_count);

bool vector_empty(const Vector * restrict vector);

void vector_at_get(const Vector * restrict vector, size_t i, void * restrict dest, size_t cell_count);

void vector_at_set(const Vector * restrict vector, size_t i, const void * restrict source, size_t cell_count);

void vector_front_get(const Vector * restrict vector, void * restrict dest, size_t cell_count);

void vector_front_set(const Vector * restrict vector, const void * restrict source, size_t cell_count);

void vector_back_get(const Vector * restrict vector, void * restrict dest, size_t cell_count);

void vector_back_set(const Vector * restrict vector, const void * restrict source, size_t cell_count);

void *vector_data(const Vector * restrict vector);

void vector_push_back(Vector * restrict vector, const void * restrict source, size_t cell_count);

void vector_pop_back(Vector * restrict vector, size_t cell_count);

void vector_iterator_insert(VectorIterator * restrict iterator, const void * source, size_t cell_count);

void vector_iterator_erase(VectorIterator * restrict iterator, size_t cell_count);

void vector_sort(const Vector * restrict vector, int (*compar)(const void *, const void *));

void vector_clear(Vector * restrict vector);

#endif