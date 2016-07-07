#ifndef _LIST_H_
#define _LIST_H_

typedef struct list List;

typedef struct list_iterator ListIterator;

List *list_create(size_t size);

void list_destroy(List * restrict list);

bool list_empty(const List * restrict list);

size_t list_size(const List * restrict list);

void list_push_front(List * restrict list, const void * restrict source);

void list_push_back(List * restrict list, const void * restrict source);

void list_front(const List * restrict list, void * restrict dest);

void list_back(const List * restrict list, void * restrict dest);

void list_pop_front(List * restrict list);

void list_pop_back(List * restrict list);

void list_remove(List * restrict list, void * restrict value);

void list_reverse(List * restrict list);

void list_clear(List * restrict list);

ListIterator *list_iterator_begin(const List * restrict list);

ListIterator *list_iterator_end(const List * restrict list);

void list_iterator_destroy(ListIterator * restrict iterator);

bool list_iterator_equal(const ListIterator * restrict iterator1, const ListIterator * restrict iterator2);

bool list_iterator_inequal(const ListIterator * restrict iterator1, const ListIterator * restrict iterator2);

bool list_iterator_dereferenceable(const ListIterator * restrict iterator);

void list_iterator_insert_front(ListIterator * restrict iterator, const void * restrict source);

void list_iterator_insert_back(ListIterator * restrict iterator, const void * restrict source);

void list_iterator_erase(ListIterator * restrict iterator);

void list_iterator_get(ListIterator * restrict iterator, void * restrict dest);

void list_iterator_set(ListIterator * restrict iterator, void * restrict source);

void list_iterator_prev(ListIterator * restrict iterator);

void list_iterator_next(ListIterator * restrict iterator);

#endif