#ifndef JULIEDS_CPU_H
#define JULIEDS_CPU_H

typedef unsigned int register_t;

typedef enum register_type {
    REG_R0, REG_R1, REG_R2, REG_R3, REG_R4, REG_R5, REG_R6, REG_R7,
    REG_R8, REG_R9, REG_R10, REG_R11, REG_R12, REG_R13, REG_R14,
    REG_PC
} register_type_t;

typedef enum cpu_mode {
    CPU_MODE_USER       = 0b10000,
    CPU_MODE_FIQ        = 0b10001,
    CPU_MODE_IRQ        = 0b10011,
    CPU_MODE_SUPERVISOR = 0b10111,
    CPU_MODE_UNDEFINED  = 0b11011,
    CPU_MODE_SYSTEM     = 0b11111
} cpu_mode_t;

typedef struct cpsr {
    cpu_mode_t mode                 : 5;
    unsigned int T                  : 1;
    unsigned int disable_fiq        : 1;
    unsigned int disable_irq        : 1;
    unsigned int A                  : 1;
    unsigned int endianness         : 1;
    unsigned int /* reserved */     : 6;
    unsigned int bla                : 4;
    unsigned int /* reserved */     : 4;
    unsigned int J                  : 1;
    unsigned int /* reserved */     : 2;
    unsigned int overflow           : 1;
    unsigned int signed_overflow    : 1;
    unsigned int carry              : 1;
    unsigned int zero               : 1;
    unsigned int negative           : 1;
} cpsr_t;

typedef struct armv5te {
    register_t registers[16];
    cpsr_t cpsr;
} armv5te_t;

#endif //JULIEDS_CPU_H