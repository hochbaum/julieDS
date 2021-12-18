#ifndef JULIEDS_CONDITION_H
#define JULIEDS_CONDITION_H

#include "armv5te/cpu.h"
#include "insn.h"

typedef enum arm_cond {
    EQ = 0b0000, // Equal
    NE = 0b0001, // Not equal
    CS = 0b0010, // Carry set
    CC = 0b0011, // Carry clear
    MI = 0b0100, // Minus
    PL = 0b0101, // Plus
    VS = 0b0110, // Overflow
    VC = 0b0111, // No overflow
    HI = 0b1000, // Higher (unsigned)
    LS = 0b1001, // Lower or same (unsigned)
    GE = 0b1010, // Greater than or equal
    LT = 0b1011, // Less than (signed)
    GT = 0b1100, // Greater than (signed)
    LE = 0b1101, // Less or equal (signed)
    AL = 0b1110, // Always
} arm_cond_t;

#define COND_FUNC(x) unsigned int armv5te_cond_##op(armv5te_t *cpu, arm_insn_t *insn)

COND_FUNC(eq);
COND_FUNC(ne);
COND_FUNC(cs);
COND_FUNC(cc);
COND_FUNC(mi);
COND_FUNC(pl);
COND_FUNC(vs);
COND_FUNC(vc);
COND_FUNC(hi);
COND_FUNC(ls);
COND_FUNC(ge);
COND_FUNC(lt);
COND_FUNC(gt);
COND_FUNC(le);
COND_FUNC(al);

#endif //JULIEDS_CONDITION_H