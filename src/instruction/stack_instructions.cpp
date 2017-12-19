#include <jvm/instruction/stack_instructions.h>

namespace cyh {
void SWAP_Instruction::Execute(JFrame& frame)
{
    auto op_stack = frame.OpStack();

    auto val1 = op_stack.Pop<LocalSlot>();
    auto val2 = op_stack.Pop<LocalSlot>();

    op_stack.Push<LocalSlot>(val1);
    op_stack.Push<LocalSlot>(val2);
}
}
