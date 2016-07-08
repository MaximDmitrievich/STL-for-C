#ifndef _MAP_H_
#define _MAP_H_

typedef struct elem_ Elem;

typedef struct map_ Map;

Map *map_create(size_t data_size, size_t key_size);
void map_insert(Map *restrict map, const void *restrict data, const void *restrict key);
void map_elem_get(Map *restrict map, void *restrict key, void *restrict destptr);
void map_elem_delete(Map *restrict map, const void *restrict key);
void map_destroy(Map *restrict map);
#endif