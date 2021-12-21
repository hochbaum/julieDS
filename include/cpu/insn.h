#ifndef JULIEDS_INSN_H
#define JULIEDS_INSN_H

#include <stdint.h>

#include "armv5te/cpu.h"

/**
 * Reads 4 bytes in little endian order from a char array.
 */
#define read_dword_le(data,i) ((data[i + 3] << 24) | (data[i + 2] << 16) | (data[i + 1] << 8) | data[i])

/**
 * Rotates (n) d bits to the right.
 */
#define rotate_dword_right(n,d) (n >> d) | (n << (32 - d))

enum arm_cond {
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
};

struct arm_insn {
    uint32_t shifter_operand    : 12;   // 11..0
    uint32_t destination        : 4;    // 15..12
    uint32_t source             : 4;    // 19..16
    uint32_t update             : 1;    // 20
    uint32_t opcode             : 4;    // 24..21
    uint32_t immediate          : 1;    // 25
    uint32_t type               : 2;    // 27..26, not sure what this is yet
    enum arm_cond condition     : 4;    // 31..28
};

#define COND_FUNC(x) uint32_t armv5te_cond_##op(struct armv5te *cpu, struct arm_insn *insn)

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

#define INSN_FUNC(op) void armv5te_##op(struct armv5te *cpu, struct arm_insn *insn)

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