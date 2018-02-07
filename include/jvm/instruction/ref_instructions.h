#ifndef TOYJVM_INSTRUCTION_REF_INSTRUCTIONS_H
#define TOYJVM_INSTRUCTION_REF_INSTRUCTIONS_H

#include <jvm/instruction/base_instruction.h>
#include <jvm/instruction/ref_instructions.h>
#include <jvm/rtdata/jvm_frame.h>
#include <jvm/rtdata/runtime_const_pool.h>
#include <jvm/rtdata/string_pool.h>
#include <jvm/rtdata/symbol_ref.h>

namespace cyh {
class NEW_Instruction : public Index16Instruction {
public:
    void Execute(JFrame* jframe) override;
};

class PUTSTATIC_Instruction : public Index16Instruction {
public:
    void Execute(JFrame* jframe) override;
};

class GETSTATIC_Instruction : public Index16Instruction {
public:
    void Execute(JFrame* jframe) override;
};

class PUTFIELD_Instruction : public Index16Instruction {
public:
    void Execute(JFrame* jframe) override;
};

class GETFIELD_Instruction : public Index16Instruction {
public:
    void Execute(JFrame* jframe) override;
};

class INSTANCEOF_Instruction : public Index16Instruction {
public:
    void Execute(JFrame*) override;
};

class CHECKCAST_Instruction : public Index16Instruction {
public:
    void Execute(JFrame*) override;
};

template <typename T>
class BaseLdcInstruction : public Index8Instruction<T> {
public:
    void Execute(JFrame*) override;
};

using LDC_Instruction = BaseLdcInstruction<u1>;
using LDC_W_Instruction = BaseLdcInstruction<u2>;
using LDC2_W_Instruction = BaseLdcInstruction<u2>;

#define LDC_CASE(ENUMTYPE, RAWTYPE)                                         \
    case ENUMTYPE: {                                                        \
	opstack.Push<RAWTYPE>(rt_const_pool->GetVal<RAWTYPE>(this->index)); \
	break;                                                              \
    }

template <typename T>
void BaseLdcInstruction<T>::Execute(JFrame* jframe)
{
    auto& opstack = jframe->OpStack();
    auto jclass = jframe->jmethod()->jclass();
    auto rt_const_pool = jclass->rt_const_pool();

    auto tag = rt_const_pool->GetType(this->index);
    switch (tag) {
	LDC_CASE(Integer, int)
	LDC_CASE(Float, float)
	LDC_CASE(Long, long)
	LDC_CASE(Double, double)
    case Klass: {
	auto class_ref = rt_const_pool->GetRef<ClassRef>(this->index);
	auto jl_class_obj = class_ref->ResolveClass()->jl_class();
	opstack.Push<JObject*>(jl_class_obj);
	break;
    }
    case String: {
	auto& str = rt_const_pool->GetVal<std::string>(this->index);
	DLOG(INFO) << "LDC string:[" << str << "]";
	auto interned_str = GetStringFromPool(jclass->class_loader(), str);
	opstack.Push<JObject*>(interned_str);
	break;
    }
    }
}
class ATHROW_Instruction : public NoOperandsInstruction {
public:
    void Execute(JFrame*) override;

private:
    bool FindAndGotoExceptionHandler(JThread* jthread, JObject*);
    void HandleUncaughtException(JThread* jthread, JObject*);
};
}
#endif /* end of include guard: TOYJVM_INSTRUCTION_REF_INSTRUCTIONS_H */
