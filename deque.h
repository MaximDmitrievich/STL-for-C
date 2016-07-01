/* 
STL for C
Structure - Deque
Works with different types
Needs included stdlib and stdbool
by Eremin M.D.
30.06.2016
*/
#define define_deque(type)\
struct _deque_##type;\
typedef struct functions_\
{\
	void (*deque_push_front)(struct _deque_##type, type);\
	void (*deque_push_back)(struct _deque_##type, type);\
	type (*deque_front)(struct _deque_##type *);\
	type (*deque_back)(struct _deque_##type *);\
	type (*deque_pop_front)(struct _deque_##type *);\
	type (*deque_pop_back)(struct _deque_##type *);\
	size_t (*deque_size)(struct _deque_##type *);\
	bool (*deque_is_empty)(struct _deque_##type *)\
	void (*deque_destroy)struct _deque_##type *);\
} Deque_interface##type;\
typedef struct deque_elem_\
{\
	type _data;\
	struct deque_elem_ *_next;\
} Deque_elem##type;\
typedef struct deque_\
{\
	Deque_elem##type *front;\
	Deque_elem##type *back;\
	size_t size;\
	Deque_interface##type *_interface;\
} Deque##type;\
void deque_push_front(Deque##type *deque, type value);\
void deque_push_back(Deque##type *deque, type value);\
type deque_front(Deque##type *deque);\
type deque_back(Deque##type *deque);\
type deque_pop_front(Deque##type *deque);\
type deque_pop_back(Deque##type *deque);\
size_t deque_size(Deque##type *deque);\
bool deque_is_empty(Deque##type *deque);\
void deque_destroy(Deque##type *deque);\
\
void deque_push_front(Deque##type *deque, type value)\
{\
	Deque_elem##type *_elem = (Deque_elem##type *) malloc(sizeof(Deque_elem##type));\
	if (deque->front == NULL && deque->back) {\

	}
	_elem->next = deque->front;\
	deque->front = _elem;\
	_elem->_data = value;\
	deque->size++;
}\
void deque_push_back(Deque##type *deque, type value)\
{\
	Deque_elem##type *_elem = (Deque_elem##type *) malloc(sizeof(Deque_elem##type));\
	_elem->next = NULL;\
	deque->back->next = _elem;\
	deque->back = _elem;\
	_elem->_data = value;\
	deque->size++;\
}\
type deque_front(Deque##type *deque)\
{\
	return deque->front._data;\
}\
type deque_back(Deque##type *deque)\
{\
	return deque->back._data;\
}\
type deque_pop_front(Deque##type *deque)\
{\
	type val = deque->front._data;\
	Deque_elem##type *temp_elem = deque->front;\
	deque->front = deque->front->next;\
	free(temp_elem);\
	temp_elem = NULL;\
	deque->size--;\
	return val;\
}\
type deque_pop_back(Deque##type *deque)\
{\
	type val = deque->back._data;\
	Deque_elem##type *temp_elem = deque->front;\
	while (temp_elem != deque->back) {\
		temp_elem->elem = temp_elem->elem->next;\
	}\
	free(deque->back);\
	deque->back = temp_elem;\
	temp_elem = NULL;\
	deque->size--;\
	return val;
}\
size_t deque_size(Deque##type *deque)\
{\
	return deque->size;\
}\
bool deque_is_empty(Deque##type *deque)\
{\
	return deque->size == 0;\
}\
void deque_destroy(Deque##type *deque)\
{\
	while (!deque_is_empty(deque)) {\
		deque_pop_back(deque);\
	}\
	free(deque);\
}\
Deque_interface##type _interface##type = {\
	&deque_push_front##type,\
	&deque_push_back##type,\
	&deque_front##type,\
	&deque_back##type,\
	&deque_pop_front##type,\
	&deque_pop_back##type,\
	&deque_size##type,\
	&deque_is_empty##type,\
	&deque_destroy##type,\
};\
Deque##type *deque_create##type()\
{\
	Deque##type *deque= (Deque##type *) malloc(sizeof(Deque##type));
	deque->front = NULL;
	deque->back = NULL;
	deque->size = 0;
	return deque;
}\
#define deque_push_front(collection, type) collection->_interface->deque_push_front(collection, type)
#define deque_push_back(collection, type) collection->_interface->deque_push_back(collection, type)
#define deque_front(collection) collection->_interface->deque_front(collection)
#define deque_back(collection) collection->_interface->deque_back(collection)
#define deque_pop_front(collection) collection->_interface->deque_pop_front(collection)
#define deque_pop_back(collection) collection->_interface->deque_pop_back(collection)
#define deque_size(collection) collection->_interface->deque_size(collection)
#define deque_is_empty(collection) collection->_interface->deque_is_empty(collection)
#define deque_destroy(collection) collection->_interface->deque_destroy(collection)
#define Deque(type) Deque_##type
#define deque_create(type) deque_create##type()
