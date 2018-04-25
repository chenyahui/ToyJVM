//
// Created by cyhone on 18-4-24.
//

#include <toyjvm/instruction/ref_instructions.h>

namespace jvm {
    void NEW_Instruction::execute(jvm::JvmFrame &frame)
    {
        const auto &rt_const_pool = frame.method()->klass()->runtimeConstPool();
        auto &class_ref = rt_const_pool.at<std::shared_ptr<ClassRef>>(this->operand_);
        auto klass = class_ref->resolveClass();
        auto obj = std::make_shared<JvmObject>(klass);
        frame.operandStack().push(obj);
    }


    void CHECKCAST_Instruction::execute(jvm::JvmFrame &frame)
    {
        auto &opstack = frame.operandStack();
        auto obj_ref = opstack.pop<std::shared_ptr<JvmRef>>();

        if (obj_ref == nullptr) {
            return;
        }
        auto tclass = frame.method()
                ->klass()
                ->runtimeConstPool().at<std::shared_ptr<ClassRef>>(this->operand_)
                ->resolveClass().get();

        if (!obj_ref->isInstanceOf(tclass)) {
            // todo throw exception
        }
    }

    void INSTANCEOF_Instruction::execute(jvm::JvmFrame &frame)
    {
        auto &opstack = frame.operandStack();
        auto obj_ref = opstack.pop<std::shared_ptr<JvmRef>>();

        if (obj_ref == nullptr) {
            opstack.push<int>(0);
            return;
        }

        auto tclass = frame.method()
                ->klass()
                ->runtimeConstPool().at<std::shared_ptr<ClassRef>>(this->operand_)
                ->resolveClass().get();

        opstack.push<int>(obj_ref->isInstanceOf(tclass));
    }
}