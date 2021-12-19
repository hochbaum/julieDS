#ifndef JULIEDS_INSN_H
#define JULIEDS_INSN_H

#include <stdint.h>

#include "armv5te/cpu.h"

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

typedef struct arm_insn {
    unsigned int shifter_operand    : 12;   // 11..0
    unsigned int destination        : 4;    // 15..12
    unsigned int source             : 4;    // 19..16
    unsigned int update             : 1;    // 20
    unsigned int opcode             : 4;    // 24..21
    unsigned int immediate          : 1;    // 25
    unsigned int                    : 2;    // 27..26, not sure what this is yet
    arm_cond_t condition            : 4;    // 31..28
} arm_insn_t;

inline arm_insn_t *insn_parse_raw(uint32_t *raw);

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

#define INSN_FUNC(op) void armv5te_##op(armv5te_t *cpu, arm_insn_t *insn)

INSN_FUNC(and);
INSN_FUNC(eor);
INSN_FUNC(sub);
INSN_FUNC(rsb);
INSN_FUNC(add);
INSN_FUNC(adc);
INSN_FUNC(sbc);
INSN_FUNC(rsc);
INSN_FUNC(tst);
INSN_FUNC(teq);
INSN_FUNC(cmp);
INSN_FUNC(cmn);
INSN_FUNC(orr);
INSN_FUNC(mov);
INSN_FUNC(bic);
INSN_FUNC(mvn);

#endif //JULIEDS_INSN_H