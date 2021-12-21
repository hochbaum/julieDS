#include <stdio.h>

#include "cpu/armv5te/cpu.h"
#include "cpu/insn.h"

#include "nds/nds.h"
#include "nds/cartridge.h"

#include <raylib.h>

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        printf("Error: please specify a ROM file\n");
        return 1;
    }

    char *filename = argv[1];
    unsigned char *data = nds_cartridge_read(filename);

    if (data == NULL)
    {
        printf("Error: could not read cartridge %s\n", filename);
        return 1;
    }

    struct nds_cartridge_header *header = (struct nds_cartridge_header *) data;

    printf("Successfully read cartridge \"%s\"\n", header->game_title);

    uint32_t arm9_rom_begin = header->arm9_rom_offset;
    uint32_t arm9_rom_end = arm9_rom_begin + header->arm9_size;

    printf("ARM9 ROM found at: 0x%08X - 0x%08X\n", arm9_rom_begin, arm9_rom_end);

    for (uint32_t i = arm9_rom_begin; i < arm9_rom_end; i += 4)
    {
        uint32_t raw_op = read_dword_le(data, i);
        struct arm_insn *insn = (struct arm_insn *) &raw_op;

        // Print some MOV ops for testing.
        if (insn->opcode == 0b1101u && insn->immediate)
        {
            uint8_t rotation = (insn->shifter_operand >> 8) & 0xF;
            uint8_t n = insn->shifter_operand & 0xFF;
            printf("%08X: MOV %s, #0x%08X\n", raw_op, register_to_str(insn->destination), rotate_dword_right(n, rotation * 2));
        }
    }

    // TODO: Find out why MeasureText returns 0?
    int top_width = MeasureText("TOP LCD", 10);
    int top_center = (NDS_SCREEN_WIDTH + top_width) / 2 - top_width;
    int bot_width = MeasureText("TOUCHSCREEN", 10);
    int bot_center = (NDS_SCREEN_WIDTH + bot_width) / 2 - bot_width;

    InitWindow(NDS_SCREEN_WIDTH, NDS_SCREEN_HEIGHT * 2, "julieDS");

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);
        for (int i = 0; i < NDS_SCREEN_WIDTH; i++) {
            DrawPixel(i, NDS_SCREEN_HEIGHT - 1, RED);
        }
        DrawText("TOP LCD", top_center, NDS_SCREEN_HEIGHT / 2, 10, WHITE);
        DrawText("TOUCHSCREEN", bot_center, NDS_SCREEN_HEIGHT / 2 + NDS_SCREEN_HEIGHT, 10, WHITE);
        EndDrawing();
    }
    return 0;
}