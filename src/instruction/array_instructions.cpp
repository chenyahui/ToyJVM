#include <glog/logging.h>
#include <jvm/instruction/array_instructions.h>

using namespace cyh;

enum {
    AT_BOOLEAN = 4,
    AT_CHAR = 5,
    AT_FLOAT = 6,
    AT_DOUBLE = 7,
    AT_BYTE = 8,
    AT_SHORT = 9,
    AT_INT = 10,
    AT_LONG = 11
};
#define GET_PARRAY(Type, Sign)           \
    case Type:                           \
	return loader->LoadClass("["#Sign"");

void NEW_ARRAY_Instruction::FetchOperands(ByteCodeReader& reader)
{
    atype_ = reader.Read<u1>();
    DLOG(INFO) << "atype" << int(atype_);
}

void NEW_ARRAY_Instruction::Execute(JFrame* frame)
{
    auto& opstack = frame->OpStack();
    auto count = opstack.Pop<int>();

    if (count < 0) {
	// TODO
    }

    auto loader = frame->jmethod()->jclass()->class_loader();
    auto array_class = GetPrimitiveArrayClass(loader);
    opstack.Push<JBaseArray*>(array_class->ArrayFactory(count));
}

JClass* NEW_ARRAY_Instruction::GetPrimitiveArrayClass(ClassLoader* loader)
{
    switch (atype_) {
	GET_PARRAY(AT_BOOLEAN, Z)
	GET_PARRAY(AT_BYTE, B)
	GET_PARRAY(AT_CHAR, C)
	GET_PARRAY(AT_SHORT, S)
	GET_PARRAY(AT_INT, I)
	GET_PARRAY(AT_LONG, J)
	GET_PARRAY(AT_FLOAT, F)
	GET_PARRAY(AT_DOUBLE, D)
    default:
	throw "invalid atype";
    }
}
void ANEW_ARRAY_Instruction::Execute(JFrame* frame)
{
    auto cp = frame->jmethod()->jclass()->rt_const_pool();
    auto class_ref = cp->GetRef<ClassRef>(index);
    auto component_class = class_ref->ResolveClass();

    auto& opstack = frame->OpStack();
    auto count = opstack.Pop<int>();

    if (count < 0) {
	// TODO
    }

    auto array_class = component_class->ArrayClass();
    opstack.Push<JBaseArray*>(array_class->ArrayFactory(count));
}

void ARRAY_LENGTH_Instruction::Execute(JFrame* frame)
{
    auto& opstack = frame->OpStack();
    auto arr_ref = opstack.Pop<JBaseArray*>();
    if (arr_ref == NULL) {
	// TODO
    }
    opstack.Push<int>(arr_ref->array_length());
}

void MULTI_ANEW_ARRAY_Instruction::FetchOperands(ByteCodeReader& reader)
{
    index_ = reader.Read<u2>();
    dimensions_ = reader.Read<u1>();
}

void MULTI_ANEW_ARRAY_Instruction::Execute(JFrame* frame)
{
    auto cp = frame->jmethod()->jclass()->rt_const_pool();
    auto class_ref = cp->GetRef<ClassRef>(index_);
    auto arr_class = class_ref->ResolveClass();

    auto& opstack = frame->OpStack();
    auto counts = PopAndCheckCounts(opstack);
    auto arr = NewMultiDArray(counts, arr_class);

    opstack.Push<JBaseArray*>(arr);
}

JBaseArray* MULTI_ANEW_ARRAY_Instruction::NewMultiDArray(std::vector<int>& counts, JClass* arr_class)
{
    auto arr = arr_class->ArrayFactory(counts[0]);
    if (counts.size() > 1) {
	auto ref_arr = dynamic_cast<JArray<JReference*>*>(arr);
	for (int i = 0; i < ref_arr->array_length(); ++i) {
	    auto vec = std::vector<int>(counts.begin() + 1, counts.end());
	    (*ref_arr)[i] = NewMultiDArray(vec, arr_class->ComponentClass());
	}
    }

    return arr;
}

std::vector<int> MULTI_ANEW_ARRAY_Instruction::PopAndCheckCounts(OperandStack& opstack)
{
    std::vector<int> counts(dimensions_);
    for (int i = dimensions_ - 1; i >= 0; i--) {
	counts[i] = opstack.Pop<int>();
	if (counts[i] < 0) {
	    // TODO
	}
    }
    return counts;
}
