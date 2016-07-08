#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <signal.h>
#include <string.h>
#include "map_def.h"

#define MAP_SIZE 32


typedef struct elem_{
	void *data;
	void *key;
	struct elem_ *next;
};

typedef struct map_{
	size_t data_size;
	size_t key_size;
	size_t avail;
	size_t occup;
	Elem **table;
};

Map *map_create(size_t data_size, size_t key_size)
{
	if (data_size < 1 && key_size < 1) {
		raise(SIGSEGV);
		return NULL;
	}
	Map *map = NULL;
	if ((map = malloc(sizeof(Map))) == NULL) {
		raise(SIGSEGV);
		return NULL;
	}
	map->avail = MAP_SIZE;
	map->occup = 0;
	map->data_size = data_size;
	map->key_size = key_size;
	if ((map->table = malloc(sizeof(Elem) * map->avail)) == NULL) {
		free(map);
		raise(SIGSEGV);
		return NULL;
	}
	for (size_t i = 0u; i < map->avail; i++) {
		map->table[i] = NULL;
	}
	return map;
}

unsigned int hash_func(Map *restrict map, void *restrict key)
{
	unsigned int hash = map->avail;
	for(size_t i = 0u; i < map->key_size; ++i)
	{   
		hash = ((hash << 5) + hash) + ((unsigned char *)key)[i];
	}
	printf("\n\n%d - номер хеша\n\n", hash % map->avail);
	return hash % map->avail;
}

void map_insert(Map *restrict map, const void *restrict data, const void *restrict key)
{
	unsigned char bin = hash_func(map, key);
	Elem *new = NULL;
	Elem *lst = NULL;
	Elem *nxt = map->table[bin];
	map->occup++;
	if (map->occup == map->avail) {
		map->avail *= 2;
		map->table = realloc(map->table, sizeof(Elem) * map->avail);
	}
	while (nxt != NULL && nxt->key != NULL && memcmp(key, nxt->key, map->key_size) > 0) {
		lst = nxt;
		nxt = nxt->next;
	}
	if (nxt != NULL && nxt->key != NULL && memcmp(key, nxt->key, map->key_size) == 0) {
		free(nxt->data);
		memcpy(nxt->data, data, sizeof(map->data_size));
	} else {
		if ((new = malloc(sizeof(Elem))) == NULL) {
			raise(SIGSEGV);
			return;
		}
		if ((new->key = malloc(sizeof(map->key_size))) == NULL) {
			free(new);
			raise(SIGSEGV);
			return;
		}
		memcpy(new->key, key, map->key_size);
		if ((new->data = malloc(sizeof(map->data_size))) == NULL) {
			free(new->key);
			free(new);
			raise(SIGSEGV);
			return;
		}
		memcpy(new->data, data, map->data_size);
		new->next = NULL;
		if (nxt == map->table[bin]) {
			new->next = nxt;
			map->table[bin] = new;
		} else if (nxt == NULL) {
			lst->next = new;
		} else {
			new->next = nxt;
			lst->next = new;
		}
	}
}

void map_elem_get(Map *restrict map, void *restrict key, void *restrict destptr) 
{
	unsigned char bin = hash_func(map, key);
	Elem *pair = map->table[bin];
	while (pair != NULL && pair->key != NULL && memcmp(key, pair->key, map->key_size) > 0) {
		pair = pair->next;
	}
	if (pair == NULL || pair->key == NULL || memcmp(key, pair->key, map->key_size) != 0) {
		return;
	} else {
		if (destptr == NULL) {
			if ((destptr = malloc(sizeof(map->data_size))) == NULL) {
				raise(SIGSEGV);
				return;
			}
			memcpy(destptr, pair->data, map->data_size);
		} else {
			memcpy(destptr, pair->data, map->data_size);
		}
	}
}

void map_elem_delete(Map *restrict map, const void *restrict key)
{
	unsigned char bin = hash_func(map, key);
	Elem *lst = NULL;
	Elem *crnt = map->table[bin];
	while (crnt != NULL && crnt->key != NULL && memcmp(key, crnt->key, map->key_size) > 0) {
		lst = crnt;
		crnt = crnt->next;
	}
	if (crnt == NULL || crnt->key == NULL || memcmp(key, crnt->key, map->key_size) != 0) {
		return;
	} else {
		if (crnt->next != NULL) {
			lst->next = crnt->next;
			free(crnt->data);
			free(crnt->key);
			free(crnt);
			map->occup--;

		} else {
			free(crnt->data);
			free(crnt->key);
			free(crnt);
			map->occup--;
		}
	}
}

void map_destroy(Map *restrict map)
{
	Elem *nxt = NULL;
	Elem *crnt = NULL;
	for (int i = 0; i < map->avail; i++) {
		if (map->table[i] == NULL) {
			continue;
		}
		while (map->table[i] != NULL) {
			crnt = map->table[i];
			if (crnt->next != NULL) {
				map->table[i] = crnt->next;
				free(crnt->data);
				free(crnt->key);
				free(crnt);
				crnt = map->table[i];
			}
		}
	}
}