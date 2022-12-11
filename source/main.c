#include <string.h>

#include "cpu/armv5te/cpu.h"
#include "cpu/insn.h"

#include "nds/nds.h"
#include "nds/cartridge.h"
#include "log/log.h"

#include <raylib.h>

#include "nds/lcd.h"

int main(int argc, char **argv) {
    if (argc < 2) {
        jlog(LL_ERR, "please specify a ROM file\n");
        return 1;
    }

    char *filename = argv[1];
    union nds_cartridge *cartridge = nds_cartridge_read(filename);
    unsigned char *data = cartridge->data;

    if (data == NULL) {
        jlog(LL_ERR, "could not read cartridge %s\n", filename);
        return 1;
    }

    struct nds_cartridge_header *header = cartridge->header;

    jlog(LL_INFO, "Successfully read cartridge \"%s\"\n", header->game_title);

    uint32_t arm9_rom_begin = header->arm9_rom_offset;
    uint32_t arm9_rom_end = arm9_rom_begin + header->arm9_size;

    jlog(LL_DEBUG, "ARM9 ROM found at: 0x%08X - 0x%08X\n", arm9_rom_begin, arm9_rom_end);

    for (uint32_t i = arm9_rom_begin; i < arm9_rom_end; i += 4) {
        uint32_t raw_op = read_dword_le(data, i);
        struct arm_insn *insn = (struct arm_insn *) &raw_op;

        // Print some MOV ops for testing.
        if (insn->opcode == 0b1101 && insn->immediate) {
            uint8_t rotation = (insn->shifter_operand >> 8) & 0xF;
            uint8_t n = insn->shifter_operand & 0xFF;
            jlog(LL_DEBUG, "%08X: MOV %s, #0x%08X\n", raw_op, register_to_str(insn->destination),
                   rotate_dword_right(n, rotation * 2));
        }
    }

    struct nds_system *nds = nds_system_new();
    mm_map_add(nds->mmap, 0, NDS_RAM_SIZE, "RAM", &nds->ram);
    mm_map_add(nds->mmap, NDS_VRAM_OFFSET, NDS_VRAM_SIZE, "vRAM", &nds->vram);

    InitWindow(NDS_SCREEN_WIDTH, NDS_SCREEN_HEIGHT * 2, "julieDS");

    int top_width = MeasureText("TOP LCD", 10);
    int top_center = (NDS_SCREEN_WIDTH + top_width) / 2 - top_width;
    int bot_width = MeasureText("TOUCHSCREEN", 10);
    int bot_center = (NDS_SCREEN_WIDTH + bot_width) / 2 - bot_width;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        // Draw pixels from video memory onto the screen (currently framebuffer mode)
        // TODO: should be moved to lcd.c or so
        for (int pixel = 0; pixel < NDS_SCREEN_PIXELS; pixel++) {
            int x = pixel % NDS_SCREEN_WIDTH;
            int y = pixel / NDS_SCREEN_WIDTH;
            DrawPixel(x, y, lcd_color_to_raylib_color(lcd_get_pixel(nds, x, y)));
        }

        DrawText("TOP LCD", top_center, NDS_SCREEN_HEIGHT / 2, 10, WHITE);
        DrawText("TOUCHSCREEN", bot_center, NDS_SCREEN_HEIGHT / 2 + NDS_SCREEN_HEIGHT, 10, WHITE);
        EndDrawing();
    }

    nds_system_destroy(nds);
    return 0;
}