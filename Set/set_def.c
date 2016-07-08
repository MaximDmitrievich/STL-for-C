#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <signal.h>
#include <string.h>
#include "set_def.h"

typedef struct _elem_{
	void *data;
	struct _elem_ *left;
	struct _elem_ *right;
	struct _elem_ *parent;
	size_t sons;
}; //Set_elem

typedef struct _set_{
	Set_elem *root;
	size_t size;
	size_t elems;
}; //Set

struct _iterator_{
	Set *set;
	Set_elem *set_elem;
};// Iterator

/*Help funcs*/

void balance(Iterator *restrict it)
{

}

/*Specs funcs*/

/*Iterator*/
Iterator *iterator_create(Set *restrict set)
{
	Iterator *it = (Iterator *) malloc(sizeof(Iterator));
	if (it == NULL) {
		raise(SIGSEGV);
		return NULL;
	}
	it->set = set;
	if (set == NULL) {
		raise(SIGSEGV);
		free(it);
		return NULL;
	}
	it->set_elem = set->root;
	return it;
}

void iterator_begin(Iterator *restrict it)
{
	it->set_elem = it->set->root;
}

void iterator_left(Iterator *restrict it)
{
	if (it->set_elem->left == NULL) {
		raise(SIGSEGV);
		return;
	} else {
		it->set_elem = it->set_elem->left;
	}
}

void iterator_right(Iterator *restrict it)
{
	if (it->set_elem->right == NULL) {
		raise(SIGSEGV);
		return;
	} else {
		it->set_elem = it->set_elem->right;
	}
}

void iterator_up(Iterator *restrict it)
{
	if (it->set_elem->parent == NULL) {
		raise(SIGSEGV);
		return;
	} else {
		it->set_elem = it->set_elem->parent;
	}
}

Set_elem *get_element(Iterator *restrict it)
{
	if (it->set_elem != NULL) {
		return it->set_elem;
	} else return NULL;
}

void get_data(Iterator *restrict it, void *restrict temp)
{
	if (it->set_elem != NULL) {
		temp = malloc(sizeof(it->set->size));
		memmove(temp, it->set_elem->data, it->set->size);
	} else {
		temp = NULL;
	}
}


/*Set*/
Set *set_create(size_t size)
{
	Set *set = (Set *) malloc(sizeof(Set));
	if (set == NULL) {
		raise(SIGSEGV);
		return NULL;
	}
	set->size = size;
	set->elems = 0;
	set->root = NULL;
	return set;
}

void set_elem_insert(Iterator *restrict it, const void *restrict data)
{
	if (it->set->root == NULL) {
		Set_elem *elem = (Set_elem *) malloc(sizeof(Set_elem));
		if (elem == NULL) {
			raise(SIGSEGV);
			return;
		}
		elem->left = NULL;
		elem->right = NULL;
		elem->parent = NULL;
		elem->data = NULL;
		elem->data = malloc(sizeof(it->set->size));
		if (elem->data = NULL) {
			raise(SIGSEGV);
			return;
		}
		memmove(elem->data, data, it->set->size);
		elem->sons = 0;
		it->set->elems++;
		it->set->root = elem;
	} else {
		Set_elem *current_elem = it->set->root;
		while (true) {
			if (memcmp(data, current_elem->data, it->set->size) > 0) {
				if (current_elem->right == NULL) {
					Set_elem *elem = (Set_elem *) malloc(sizeof(Set_elem));
					if (elem == NULL) {
						raise(SIGSEGV);
						return;
					}
					elem->left = NULL;
					elem->right = NULL;
					elem->parent = current_elem;
					elem->data = NULL;
					elem->data = malloc(sizeof(it->set->size));
					if (elem->data = NULL) {
						raise(SIGSEGV);
						return;
					}
					memmove(elem->data, data, it->set->size);
					elem->sons = 0;
					current_elem->right = elem;
					it->set->elems++;
					break;
				} else {
					current_elem->sons++;
					current_elem = current_elem->right;
				}
			} else if (memcmp(data, current_elem->data, it->set->size) < 0) {
				if (current_elem->left == NULL) {
					Set_elem *elem = (Set_elem *) malloc(sizeof(Set_elem));
					if (elem == NULL) {
						raise(SIGSEGV);
						return;
					}
					elem->left = NULL;
					elem->right = NULL;
					elem->parent = current_elem;
					elem->data = NULL;
					elem->data = malloc(sizeof(it->set->size));
					if (elem->data = NULL) {
						raise(SIGSEGV);
						return;
					}
					memmove(elem->data, data, it->set->size);
					elem->sons = 0;
					current_elem->left = elem;
					it->set->elems++;
					break;
				} else {
					current_elem->sons++;
					current_elem = current_elem->left;
				}
			} else {
				break;
			}
		}
	}
}

void set_elem_delete(Iterator *restrict it)
{
	if (it->set_elem->left == NULL && it->set_elem->right == NULL) {
		Set_elem *tmp = it->set_elem;
		iterator_up(it);
		if (memcmp(tmp->data, it->set_elem->right->data, it->set->size) == 0) {
			it->set_elem->right = NULL;
		}
		if (memcmp(tmp->data, it->set_elem->left->data, it->set->size) == 0) {
			it->set_elem->left = NULL;
		}
		while (it->set_elem->parent != NULL) {
			it->set_elem->sons--;
			iterator_up(it);
		}
		free(tmp->data);
		free(tmp);
		tmp = NULL;
		balance(it);
	} else if (it->set_elem->left && it->set_elem->right == NULL) {
		Set_elem *tmp = it->set_elem;
		Set_elem *parent = it->set_elem->parent;
		iterator_left(it);
		while (it->set_elem->right != NULL) {
			iterator_right(it);
		}
		Set_elem *tmp_2 = get_element(it);
		if (memcmp(tmp->data, parent->right->data, it->set->size) == 0) {
			parent->right = tmp_2;
			it->set_elem = parent;
			iterator_right(it);
		}
		if (memcmp(tmp->data, parent->left->data, it->set->size) == 0) {
			parent->left = tmp_2;
			it->set_elem = parent;
			iterator_left(it);
		}
		if (it->set_elem->left == NULL) {
			it->set_elem->left = tmp->left;
			free(tmp->data);
			free(tmp);
			tmp = NULL;
			balance(it);
		} else {
			Set_elem *new_sons = it->set_elem->left;
			it->set_elem->left = tmp->left;
			free(tmp->data);
			free(tmp);
			tmp = NULL;
			while (true) {
				if (memcmp(new_sons->data, it->set_elem->data, it->set->size) < 0) {
					if (it->set_elem->left == NULL) {
						it->set_elem->left = new_sons;
						break;
					} else {
						iterator_left(it);
					}
				} else if (memcmp(new_sons->data, it->set_elem->data, it->set->size) > 0) {
					if (it->set_elem->right == NULL) {
						it->set_elem->right = new_sons;
						break;
					} else {
						iterator_right(it);
					}
				}
			}
		}

	} else if (it->set_elem->left == NULL && it->set_elem->right) {
		Set_elem *tmp = it->set_elem;
		Set_elem *parent = it->set_elem->parent;
		iterator_right(it);
		while (it->set_elem->left != NULL) {
			iterator_left(it);
		}
		Set_elem *tmp_2 = get_element(it);
		if (memcmp(tmp->data, parent->right->data, it->set->size) == 0) {
			parent->right = tmp_2;
			it->set_elem = parent;
			iterator_right(it);
		}
		if (memcmp(tmp->data, parent->left->data, it->set->size) == 0) {
			parent->left = tmp_2;
			it->set_elem = parent;
			iterator_left(it);
		}
		if (it->set_elem->right == NULL) {
			it->set_elem->right = tmp->left;
			free(tmp->data);
			free(tmp);
			tmp = NULL;
			balance(it);
		} else {
			Set_elem *new_sons = it->set_elem->right;
			it->set_elem->right = tmp->right;
			free(tmp->data);
			free(tmp);
			tmp = NULL;
			while (true) {
				if (memcmp(new_sons->data, it->set_elem->data, it->set->size) < 0) {
					if (it->set_elem->left == NULL) {
						it->set_elem->left = new_sons;
						balance(it);
						break;
					} else {
						iterator_left(it);
					}
				} else if (memcmp(new_sons->data, it->set_elem->data, it->set->size) > 0) {
					if (it->set_elem->right == NULL) {
						it->set_elem->right = new_sons;
						balance(it);
						break;
					} else {
						iterator_right(it);
					}
				}
			}
		}
	} else if (it->set_elem->left && it->set_elem->right) {
		Set_elem *tmp = it->set_elem;
		Set_elem *parent = it->set_elem->parent;
		Set_elem *left = it->set_elem->left;
		Set_elem *right = it->set_elem->right;
		iterator_up(it);
		if (memcmp(tmp, parent->right, it->set->size) == 0) {
			parent->right = right;
			iterator_right(it);
		} else if (memcmp(tmp, parent->left, it->set->size) == 0) {
			parent->left = right;
			iterator_left(it);
		}
		free(tmp->data);
		free(tmp);
		if (right->left == NULL) {
			right->left = left;
		} else {
			while (true) {
				if (memcmp(left->data, it->set_elem->data, it->set->size) < 0) {
					if (it->set_elem->left == NULL) {
						it->set_elem->left = left;
						balance(it);
						break;
					} else {
						iterator_left(it);
					}
				} else if (memcmp(left->data, it->set_elem->data, it->set->size) > 0) {
					if (it->set_elem->right == NULL) {
						it->set_elem->right = left;
						balance(it);
						break;
					} else {
						iterator_right(it);
					}
				}
			}
		}
	}
}

void set_destroy(Iterator *restrict it)
{
	iterator_begin(it);
	while (it->set->root != NULL) {
		set_elem_delete(it);
		iterator_begin(it);
	}
	free(it->set);
	it->set = NULL;
	free(it->set_elem);
	it->set_elem = NULL;
	free(it);
}