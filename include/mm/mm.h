#ifndef JULIEDS_MM_H
#define JULIEDS_MM_H

#include <stddef.h>

typedef unsigned int addr;

struct mem_map_entry {
    addr addr;
    unsigned int len;
    char name[16];

    void *ptr;
    struct mem_map_entry *next;
};

struct mem_map {
    struct mem_map_entry *head;
};

void mm_map_add(struct mem_map *map, addr addr, unsigned int len, const char *name, void *ptr);

struct mem_map_entry *mm_map_get(struct mem_map *map, addr addr);

#endif //JULIEDS_MM_H