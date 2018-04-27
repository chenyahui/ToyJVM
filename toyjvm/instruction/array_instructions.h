//
// Created by cyhone on 18-4-27.
//

#ifndef TOYJVM_ARRAY_INSTRUCTIONS_H
#define TOYJVM_ARRAY_INSTRUCTIONS_H

#include <toyjvm/instruction/base_instruction.h>
namespace jvm{
    class NEWARRAY_Instruction : public BaseOneOperandInstruction<u1>{
    public:
        void execute(JvmFrame &frame) override;
    };

    class ANEWARRAY_Instruction: public BaseOneOperandInstruction<u2>{
        void execute(JvmFrame &frame) override;
    };

    class ARRAYLENGTH_Instruction: public BaseInstruction{
        void execute(JvmFrame &frame) override;
    };
}
#endif //TOYJVM_ARRAY_INSTRUCTIONS_H
