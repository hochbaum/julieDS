#ifndef JULIEDS_SET_H
#define JULIEDS_SET_H

#include "cpu.h"
#include "../insn.h"

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

#endif //JULIEDS_SET_H