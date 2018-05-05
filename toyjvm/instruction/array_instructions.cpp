//
// Created by cyhone on 18-4-27.
//

#include <toyjvm/instruction/array_instructions.h>
#include <toyjvm/runtime/class_loader.h>
#include <toyjvm/runtime/symbol_ref.h>
#include <toyjvm/runtime/jvm_reference.h>

namespace jvm {
    static const std::unordered_map<int, char> arrayTypeMap = {
            {4,  'Z'},
            {5,  'C'},
            {6,  'F'},
            {7,  'D'},
            {8,  'B'},
            {9,  'S'},
            {10, 'I'},
            {11, 'J'},
    };


    void NEWARRAY_Instruction::execute(jvm::JvmFrame &frame)
    {
        auto &opstack = frame.operandStack();
        auto count = opstack.pop<u4>();

        auto result = arrayTypeMap.find(this->operand_);
        assert(result != arrayTypeMap.end());

        std::string array_type = "[";
        array_type += result->second;

        auto array_class = Loader::instance()->loadArrayClass(array_type);
        opstack.push<JvmBaseArray*>(array_class->arrayFactory(count));
    }

    void ANEWARRAY_Instruction::execute(jvm::JvmFrame &frame)
    {
        const auto &const_pool = frame.method()->klass()->runtimeConstPool();
        auto class_ref = const_pool.at<std::shared_ptr<ClassRef>>(this->operand_);
        auto component_class = class_ref->resolveClass();

        auto &opstack = frame.operandStack();
        auto count = opstack.pop<u4>();

        std::string array_type = "[";
        array_type += component_class->classDescriptor();

        auto array_class = Loader::instance()->loadArrayClass(array_type);
        opstack.push<JvmBaseArray*>(array_class->arrayFactory(count));
    }

    void ARRAYLENGTH_Instruction::execute(jvm::JvmFrame &frame)
    {
        auto &opstack = frame.operandStack();
        auto arr_ref = opstack.pop<std::shared_ptr<JvmBaseArray>>();

        if (arr_ref == nullptr) {
            // todo nullptr exception
        }
        opstack.push<int>(arr_ref->arrayLen());
    }
}