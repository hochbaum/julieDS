#ifndef JULIEDS_CPU_H
#define JULIEDS_CPU_H

#include <stdint.h>

typedef unsigned int arm_register_t;

/**
 * The 16 registers of the CPUs in the Nintendo DS system.
 * The registers are split into banked and unbanked registers.
 *
 * Unbanked registers R0-R7:
 *  An unbanked register is independent of the current \ref cpu_mode. It always refers to
 *  the same 32 bit space regardless and can be used whenever a general purpose register
 *  is needed.
 *
 * Banked registers R8-R14:
 *  The banked registers point to a 32 bit space depending on the current \ref cpu_mode.
 *  TODO: Support banked registers by not using a simple single dimensional array.
 */
enum register_type {
    REG_R0, REG_R1, REG_R2, REG_R3, REG_R4, REG_R5, REG_R6, REG_R7,
    REG_R8, REG_R9, REG_R10, REG_R11, REG_R12, REG_R13, REG_R14,
    REG_PC
};

char *register_to_str(enum register_type type);

enum cpu_mode {
    CPU_MODE_USER       = 0b10000,
    CPU_MODE_FIQ        = 0b10001,
    CPU_MODE_IRQ        = 0b10011,
    CPU_MODE_SUPERVISOR = 0b10111,
    CPU_MODE_UNDEFINED  = 0b11011,
    CPU_MODE_SYSTEM     = 0b11111
};

typedef struct cpsr {
    enum cpu_mode mode          : 5;
    uint32_t T                  : 1;
    uint32_t disable_fiq        : 1;
    uint32_t disable_irq        : 1;
    uint32_t A                  : 1;
    uint32_t endianness         : 1;
    uint32_t /* reserved */     : 6;
    uint32_t bla                : 4;
    uint32_t /* reserved */     : 4;
    uint32_t J                  : 1;
    uint32_t /* reserved */     : 2;
    uint32_t overflow           : 1;
    uint32_t signed_overflow    : 1;
    uint32_t carry              : 1;
    uint32_t zero               : 1;
    uint32_t negative           : 1;
} cpsr_t;

struct armv5te {
    arm_register_t unbanked[8];
    arm_register_t banked[8][6];
    cpsr_t cpsr;
};

uint32_t armv5te_get_register(enum register_type reg);

void armv5te_set_register(enum register_type reg, uint32_t value);

#endif //JULIEDS_CPU_H