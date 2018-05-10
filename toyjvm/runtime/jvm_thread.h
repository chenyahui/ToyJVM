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

        JvmFrame *pop();

        void push(JvmFrame *);

        JvmFrame *top() const;

        bool empty() const;

        void clear();

        std::vector<JvmFrame *> &frames();

    private:
        size_t pc_ = 0;
        std::vector<JvmFrame *> stack_;
    };
}
#endif //TOYJVM_JVM_THREAD_H
