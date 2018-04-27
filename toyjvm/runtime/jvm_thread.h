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
    private:
        int pc_;
        std::vector<JvmFrame> stack_;
    };
}
#endif //TOYJVM_JVM_THREAD_H
