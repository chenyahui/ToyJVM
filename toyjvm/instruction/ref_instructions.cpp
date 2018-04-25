//
// Created by cyhone on 18-4-24.
//

#include <toyjvm/instruction/ref_instructions.h>
#include <toyjvm/runtime/symbol_ref.h>

namespace jvm {
    void NEW_Instruction::execute(jvm::JvmFrame &frame)
    {
        const auto &rt_const_pool = frame.method()->klass()->runtimeConstPool();
        auto &class_ref = rt_const_pool.at<std::shared_ptr<ClassRef>>(operand_);
        auto klass = class_ref->resolveClass();
        auto obj = std::make_shared<JvmObject>(klass);
        frame.operandStack().push(obj);
    }
}