//
// Created by cyhone on 18-5-6.
//
#include <toyjvm/instruction/invoke_instructions.h>
#include <toyjvm/runtime/jvm_thread.h>

namespace jvm {


    void BaseInvokeInstruction::invokeMethod(jvm::JvmFrame &invoker, jvm::JvmMethod *method)
    {
        auto &thread = invoker.thread();
        auto new_frame = new JvmFrame(thread, method);
        thread.push(new_frame);


    }
}
