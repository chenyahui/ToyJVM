#include <glog/logging.h>
#include <jvm/instruction/math_instructions.h>

namespace cyh {
void IINC_Instruction::FetchOperands(ByteCodeReader& reader)
{
    index = static_cast<int>(reader.Read<u1>());
    const_ = static_cast<int>(reader.Read<j_byte>());
}
void IINC_Instruction::Execute(JFrame* frame)
{
    DLOG(INFO) << "index = " << index
	       << " const = " << const_;

    auto& local_vars = frame->LocalVars();
    auto val = local_vars.Get<j_int>(index);
    local_vars.Set<j_int>(index, val + const_);
}
}
