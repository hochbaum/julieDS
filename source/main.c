#include <stdio.h>

#include "cpu/armv5te/cpu.h"
#include "nds/cartridge.h"

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        printf("error: please specify a ROM file\n");
        return 1;
    }

    char *filename = argv[0];
    char *data = nds_cartridge_read(filename);

    if (data == NULL)
    {
        printf("error: could not read cartridge %s\n", filename);
        return 1;
    }

    struct nds_cartridge_header *header = (struct nds_cartridge_header *) data;

    printf("%s\n", header->game_title);
    printf("0x%x\n", header->arm9_entry_addr);
    return 0;
}