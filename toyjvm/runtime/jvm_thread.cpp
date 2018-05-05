//
// Created by cyhone on 18-4-27.
//
#include <toyjvm/runtime/jvm_thread.h>

namespace jvm {
    JvmFrame* JvmThread::pop()
    {
        auto result = stack_.back();
        stack_.pop_back();
        return result;
    }

    void JvmThread::push(jvm::JvmFrame* frame)
    {
        stack_.push_back(frame);
    }

    JvmFrame* JvmThread::top() const
    {
        return stack_.back();
    }

    bool JvmThread::empty() const
    {
        return stack_.empty();
    }
}
