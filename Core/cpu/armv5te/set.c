#include "../../../include/cpu/armv5te/set.h"

INSN_FUNC(add)
{
    // TODO: Check for condition...
    uint32_t condition_passed = 1;
    uint32_t carry_flag = 0;

    if (condition_passed)
    {
        uint32_t rd = cpu->registers[insn->destination];
        uint32_t rn = cpu->registers[insn->source];
        rd = rn + insn->shifter_operand + carry_flag;

        uint32_t S = 0;
        if (S && insn->destination == REG_PC)
        {

        }
    }
}