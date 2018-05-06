//
// Created by cyhone on 18-4-27.
//

#include <toyjvm/runtime/jvm_frame.h>
#include <toyjvm/runtime/jvm_thread.h>

namespace jvm {
    JvmFrame::JvmFrame(jvm::JvmThread &thread, jvm::JvmMethod *method)
            : thread_(thread),
              method_(method),
              local_slots_(method->maxLocals()),
              operand_stack_(method->maxStack())
    {}

    void JvmFrame::jumpToBranch(int offset)
    {
        next_pc_ = thread_.pc() + offset;
    }
}