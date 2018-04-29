//
// Created by cyhone on 18-4-16.
//

#ifndef TOYJVM_JVM_THREAD_H
#define TOYJVM_JVM_THREAD_H

#include <vector>
#include <toyjvm/runtime/jvm_frame.h>
#include <boost/noncopyable.hpp>

namespace jvm {
    class JvmThread : boost::noncopyable {
    public:
        size_t pc() const
        {
            return pc_;
        }

        std::shared_ptr<JvmFrame> pop();

        void push(std::shared_ptr<JvmFrame>);

        std::shared_ptr<JvmFrame> top() const;

        bool empty() const;
    private:
        size_t pc_;
        std::vector<std::shared_ptr<JvmFrame>> stack_;
    };
}
#endif //TOYJVM_JVM_THREAD_H
