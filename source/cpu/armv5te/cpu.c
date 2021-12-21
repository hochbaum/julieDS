#include "cpu/armv5te/cpu.h"

char *register_to_str(enum register_type type)
{
    static char *names[] = {
            "R0",
            "R1",
            "R2",
            "R3",
            "R4",
            "R5",
            "R6",
            "R7",
            "R8",
            "R9",
            "R10",
            "R11",
            "R12",
            "R13",
            "R14",
            "PC"
    };
    return names[type];
}