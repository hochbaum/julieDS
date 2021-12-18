#ifndef JULIEDS_INSN_H
#define JULIEDS_INSN_H

#include <stdint.h>

#include "condition.h"

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

#endif //JULIEDS_INSN_H