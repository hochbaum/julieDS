#ifndef JULIEDS_NDS_H
#define JULIEDS_NDS_H

#define NDS_SCREEN_WIDTH    (256*2)
#define NDS_SCREEN_HEIGHT   (192*2)
#define NDS_SCREEN_PIXELS   (NDS_SCREEN_WIDTH*NDS_SCREEN_HEIGHT)
#define NDS_RAM_SIZE        (4*1024*1024) // First NDS model, DSi has 16MiB.

#define NDS_VRAM_OFFSET     0x6800000
#define NDS_VRAM_SIZE       (656*1024)

#define NDS_IO_OFFSET       0x4000000
#define NDS_POWCNT_1        (NDS_IO_OFFSET + 0x304)
#define NDS_DISPCNT         (NDS_IO_OFFSET + 0x1000)
#define NDS_VRAMCNT_A       (NDS_IO_OFFSET + 0x240)

#include "cpu/armv5te/cpu.h"
#include "mm/mm.h"

struct nds_system {
    struct mem_map *mmap;
    struct armv5te *arm9;

    char ram[NDS_RAM_SIZE];
    char vram[NDS_VRAM_SIZE];
};

void nds_system_init(struct nds_system *nds);

void nds_mem_read(struct nds_system *nds, addr addr, unsigned int n, char *buf);

#endif //JULIEDS_NDS_H