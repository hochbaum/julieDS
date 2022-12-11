#ifndef JULIEDS_NDS_H
#define JULIEDS_NDS_H

#define NDS_SCALE 2
#define NDS_SCREEN_WIDTH    (256*NDS_SCALE)
#define NDS_SCREEN_HEIGHT   (192*NDS_SCALE)
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

struct lcd_color {
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

struct nds_system {
    struct mem_map *mmap;
    struct armv5te *arm9;

    unsigned char ram[NDS_RAM_SIZE];

    union {
        unsigned char data[NDS_VRAM_SIZE];
        struct lcd_color framebuf[NDS_VRAM_SIZE / 3]; // Divide by 3 because we are using 24 bits per entry
    } vram;
};

// Clean up using nds_system_destroy
struct nds_system *nds_system_new();

void nds_system_destroy(struct nds_system *nds);

void nds_mem_read(struct nds_system *nds, addr addr, unsigned int n, char *buf);

#endif //JULIEDS_NDS_H