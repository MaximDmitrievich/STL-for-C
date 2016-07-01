/* 
STL for C
Structure - Queue
Works with different types
Needs included stdlib and stdbool
by Eremin M.D.
30.06.2016
*/
#define define_queue(type)\
struct _queue_##type;\
typedef struct functions_\
{\
	void (*queue_push)(struct _queue_##type *, type);\
	size_t (*queue_size)(struct _queue_##type *);\
	type (*queue_pop)(struct _queue_##type *);\
	type (*queue_front)(struct _queue_##type *);\
	type (*queue_back)(struct _queue_##type *);\
	bool (*queue_is_empty)(struct _queue_##type *);\
	void (*queue_destroy)(struct _queue_##type *);\
} Queue_interface_##type;\
\
typedef struct _queue_elem_##type \
{\
	type _data;\
	struct _queue_elem_##type *_next;\
} Queue_elem_##type;\
\
typedef struct _queue_##type \
{\
	Queue_elem_##type *front;\
	Queue_elem_##type *back;\
	size_t size;\
	Queue_interface_##type *_interface;\
} Queue_##type;\
\
void queue_push(Queue_##type *queue, type value);\
size_t queue_size(Queue_##type *queue);\
type queue_pop(Queue_##type *queue);\
type queue_front(Queue_##type *queue);\
type queue_back(Queue_##type *queue);\
bool queue_is_empty(Queue_#type *queue);\
void queue_destroy(Queue_##type *queue);\
\
void queue_push(Queue_##type *queue, type value)\
{\
	Queue_elem_##type *elem = (Queue_elem_##type *) malloc(sizeof(Queue_elem_##type));\
	elem->_next = NULL;\
	if (queue->front == NULL && queue->back == NULL) {\
		queue->front = elem;\
		queue->back = elem;\
	} else {\
		queue->back->_next = elem;\
		queue->back = elem;\
	}\
	elem->_data = value;\
	queue->size++;\
}\
size_t queue_size(Queue_##type *queue)\
{\
	return queue->size;\
}\
type queue_pop(Queue_##type *queue)\
{\
	type value = queue->front->_data;\
	Queue_elem_##type *tmp = queue->front;\
	queue->front = queue->front->_next;\
	free(tmp);\
	*tmp = NULL;\
	queue->size--;\
	return value;\
}\
type queue_front(Queue_##type *queue)\
{\
	return queue->front->_data;\
}\
type queue_back(Queue_##type *queue)\
{\
	return queue->back->_data;\
}\
bool queue_is_empty(Queue_##type *queue)\
{\
	return queue->size == 0;\
}\
void queue_destroy(Queue_##type *queue)\
{\
	while (!queue_is_empty(queue) {\
		queue_pop(queue);\
	}\
	free(queue);\
	queue = NULL;\
}\
\
Queue_interface_##type _interface##type = { \
	&queue_push,\
	&queue_size,\
	&queue_pop,\
	&queue_front,\
	&queue_back,\
	&queue_is_empty,\
	&queue_destroy,\
};\
Queue_##type *queue_create##type()\
{\
	Queue_##type *queue = (Queue_##type *) malloc(sizeof(Queue_##type));\
	queue->front = NULL;\
	queue->back = NULL;\
	queue->size = 0;\
	return queue;\
}\

#define queue_push(collection, elem) collection->_interface->queue_push(collection, elem)
#define queue_size(collection) collection->_interface->queue_size(collection)
#define queue_pop(collection) collection->_interface->queue_pop(collection)
#define queue_front(collection) collection->_interface->queue_front(collection)
#define queue_back(collection) collection->_interface->queue_back(collection)
#define queue_is_empty(collection) collection->_interface->queue_is_empty(collection)
#define queue_destroy(collection) collection->_interface->queue_destroy(collection)
#define Queue(type) Queue_##type
#define queue_create(type) queue_create##type()