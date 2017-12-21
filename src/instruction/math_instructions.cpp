#include <jvm/instruction/math_instructions.h>

namespace cyh {
void IINC_Instruction::FetchOperands(ByteCodeReader& reader)
{
    index = reader.Read<u4>();
    const_ = reader.Read<j_int>();
}
void IINC_Instruction::Execute(JFrame* frame)
{
    auto local_vars = frame->LocalVars();

    auto val = local_vars.Get<j_int>(index);
    val += const_;

    local_vars.Set<j_int>(index, val);
}
}
