#include "nds/nds.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void nds_system_init(struct nds_system *nds) {
    nds->mmap = malloc(sizeof(struct mem_map));
}