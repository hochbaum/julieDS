#include "nds/nds.h"

#include <stdlib.h>
#include <raylib.h>

struct nds_system *nds_system_new() {
    struct nds_system *nds = malloc(sizeof(struct nds_system));
    nds->mmap = malloc(sizeof(struct mem_map));
    return nds;
}

void nds_system_destroy(struct nds_system *nds) {
    free(nds->mmap);
    free(nds);
}