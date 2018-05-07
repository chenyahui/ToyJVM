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

    static JvmBaseArray *buildArrayWithDescriptor(size_t count, const std::string &descriptor)
    {
        std::string array_type = "[";
        array_type += descriptor;
        auto array_class = Loader::instance()->loadArrayClass(array_type);
        return array_class->arrayFactory(count);
    }

    static JvmBaseArray *buildArrayWithDescriptor(size_t count, char descriptor)
    {
        return buildArrayWithDescriptor(count, std::string(1, descriptor));
    }

    void NEWARRAY_Instruction::execute(jvm::JvmFrame &frame)
    {
        auto &opstack = frame.operandStack();
        auto count = opstack.pop<u4>();

        auto result = arrayTypeMap.find(this->operand_);
        assert(result != arrayTypeMap.end());

        opstack.push<jarr>(buildArrayWithDescriptor(count, result->second));
    }

    void ANEWARRAY_Instruction::execute(jvm::JvmFrame &frame)
    {
        const auto &const_pool = frame.method()->klass()->runtimeConstPool();
        auto class_ref = const_pool.at<std::shared_ptr<ClassRef>>(this->operand_);
        auto component_class = class_ref->resolveClass();

        auto &opstack = frame.operandStack();
        auto count = opstack.pop<u4>();


        opstack.push<jarr>(buildArrayWithDescriptor(count, component_class->descriptor()));
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

    void MULTIANEWARRAY_Instruction::fetchOperands(jvm::ByteCodeReader &reader)
    {
        index_ = reader.read<u4>();
        dimensions_ = reader.read<u1>();
    }

    void MULTIANEWARRAY_Instruction::execute(jvm::JvmFrame &frame)
    {
        auto &const_pool = frame.method()->klass()->runtimeConstPool();
        auto class_ref = const_pool.at<ClassRef *>(index_);
        auto component_class = class_ref->resolveClass();

        auto &opstack = frame.operandStack();
        auto counts = popAndCheckCounts(opstack);
        auto arr = newMultiDArray(counts, component_class);

        opstack.push<jarr>(arr);
    }

    std::vector<int> MULTIANEWARRAY_Instruction::popAndCheckCounts(OperandStack &opstack)
    {
        std::vector<int> counts(dimensions_);
        for (int i = dimensions_ - 1; i >= 0; i--) {
            counts[i] = opstack.pop<int>();
            if (counts[i] < 0) {
                // TODO
            }
        }
        return counts;
    }

    // todo 似乎有问题
    JvmBaseArray *MULTIANEWARRAY_Instruction::newMultiDArray(std::vector<int> &counts,
                                                             jvm::JvmClass *component_class)
    {
        auto arr = buildArrayWithDescriptor(counts[0], component_class->descriptor());
        if (counts.size() > 1) {
            auto ref_arr = dynamic_cast<JvmArray<JvmRef *> *> (arr);
            for (int i = 0; i < ref_arr->arrayLen() ;++i) {
                auto vec = std::vector<int>(counts.begin() + 1, counts.end());
                ref_arr->set(i, newMultiDArray(vec, component_class));
            }
        }

        return arr;
    }

}