//
// Created by cyhone on 18-4-27.
//

#include <toyjvm/interpreter/interpret.h>
#include <toyjvm/runtime/jvm_thread.h>

namespace jvm {
    void interpret(JvmMethod *method)
    {
        JvmThread athread;
        auto frame = new JvmFrame(athread, method);
        athread.push(frame);


    }

}