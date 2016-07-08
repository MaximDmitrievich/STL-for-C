#ifndef _SET_H_
#define _SET_H_

typedef struct _elem_ Set_elem;
typedef struct _set_ Set;

typedef struct _iterator_ Iterator;

Iterator *iterator_create(Set *restrict set);
void iterator_begin(Iterator *restrict it);
void iterator_left(Iterator *restrict it);
void iterator_right(Iterator *restrict it);
void iterator_up(Iterator *restrict it);
Set_elem *get_element(Iterator *restrict it);
void get_data(Iterator *restrict it, void *restrict temp);

Set *set_create(size_t size);
void set_elem_insert(Iterator *restrict it, const void *restrict data);
void set_elem_delete(Iterator *restrict it);
void set_destroy(Iterator *restrict it);
#endif