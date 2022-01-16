#include "mm/mm.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void mm_map_add(struct mem_map *map, addr addr, unsigned int len, const char *name, void *ptr) {
    struct mem_map_entry *head = map->head;
    struct mem_map_entry *new = malloc(sizeof(struct mem_map_entry));
    new->addr = addr;
    new->next = head;
    new->len = len;
    new->ptr = ptr;
    strcpy(new->name, name);
    map->head = new;

    printf("Mapped memory 0x%08X - 0x%08X as %s\n", addr, addr + len, new->name);
}

struct mem_map_entry *mm_map_get(struct mem_map *map, addr addr) {
    struct mem_map_entry *current = map->head;
    while (current) {
        if (addr >= current->addr && addr <= (current->addr + current->len)) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}