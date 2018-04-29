//
// Created by cyhone on 18-4-27.
//
#include <toyjvm/runtime/jvm_thread.h>

namespace jvm {
    std::shared_ptr<JvmFrame> JvmThread::pop()
    {
        auto result = stack_.back();
        stack_.pop_back();
        return result;
    }

    void JvmThread::push(std::shared_ptr<jvm::JvmFrame> frame)
    {
        stack_.push_back(frame);
    }

    std::shared_ptr<JvmFrame> JvmThread::top() const
    {
        return stack_.back();
    }

    bool JvmThread::empty() const
    {
        return stack_.empty();
    }
}
