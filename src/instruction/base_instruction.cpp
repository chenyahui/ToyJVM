#include <jvm/instruction/base_instruction.h>

namespace cyh {
void BranchJump(JFrame& frame, int offset)
{
    auto thread = frame.Thread();
    auto nextpc = thread->Pc() + offset;

    thread->SetNextPc(nextpc);
}
}
