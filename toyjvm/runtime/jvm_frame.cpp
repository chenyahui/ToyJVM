//
// Created by cyhone on 18-4-27.
//

#include <toyjvm/runtime/jvm_frame.h>
#include <toyjvm/runtime/jvm_thread.h>

namespace jvm {
    void JvmFrame::jumpToBranch(int offset)
    {
        next_pc_ = thread_.pc() + offset;
    }
}