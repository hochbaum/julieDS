#ifndef JULIEDS_CARTRIDGE_H
#define JULIEDS_CARTRIDGE_H

#include <stdint.h>

#define bytes(n) n*8

enum nds_unit_type {
    NDS         = 0x00,
    DSI         = 0x01,
    NDS_DSI     = 0x02,
    DSI2        = 0x03,
};

struct nds_cartridge_header {
    char game_title[12];
    uint32_t game_code                  : bytes(4);
    uint32_t maker_code                 : bytes(2);
    enum nds_unit_type unit_code        : bytes(1);
    uint32_t encryption_seed            : bytes(1);
    uint32_t device_capacity            : bytes(1);
    char _reserved0[7];                 // Reserved
    uint32_t revision                   : bytes(2);
    uint32_t rom_version                : bytes(1);
    uint32_t internal_flags             : bytes(1);
    uint32_t arm9_rom_offset            : bytes(4);
    uint32_t arm9_entry_addr            : bytes(4);
    uint32_t arm9_load_addr             : bytes(4);
    uint32_t arm9_size                  : bytes(4);
    uint32_t arm7_rom_offset            : bytes(4);
    uint32_t arm7_entry_addr            : bytes(4);
    uint32_t arm7_load_addr             : bytes(4);
    uint32_t arm7_size                  : bytes(4);
    uint32_t fnt_offset                 : bytes(4);
    uint32_t fnt_len                    : bytes(4);
    uint32_t fat_offset                 : bytes(4);
    uint32_t fat_len                    : bytes(4);
    uint32_t arm9_ol_offset             : bytes(4);
    uint32_t arm9_ol_size               : bytes(4);
    uint32_t arm7_ol_offset             : bytes(4);
    uint32_t arm7_ol_size               : bytes(4);
    uint32_t ccr_ops_normal             : bytes(4);
    uint32_t ccr_ops_secure             : bytes(4);
    uint32_t icon_offset                : bytes(4);
    uint32_t secure_crc                 : bytes(2);
    uint32_t secure_transfer_timeout    : bytes(2);
    uint32_t arm9_autoload              : bytes(4);
    uint32_t arm7_autoload              : bytes(4);
    uint64_t secure_disable             : bytes(8);
    uint32_t ntr_region_rom_size        : bytes(4);
    uint32_t header_size                : bytes(4);
    char _reserved1[56];                // Reserved
    char nintendo_logo[156];
    uint32_t nintendo_logo_crc          : bytes(2);
    uint32_t header_crc                 : bytes(2);
    char _reserved2[32];                // Reserved
};

char *nds_cartridge_read(const char *path);

#endif //JULIEDS_CARTRIDGE_H