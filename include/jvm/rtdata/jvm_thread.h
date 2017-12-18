#ifndef MY_JVM_RTDATA_JVM_THREAD_H
#define MY_JVM_RTDATA_JVM_THREAD_H

#include <jvm/classfile/constant_pool.h>
#include <jvm/utils/unsafe.h>
#include <stack>
#include <vector>

namespace cyh {
class JFrame;

using JStack = std::stack<JFrame*>;

class JThread {
public:
    void SetNextPc(int pc);
    int Pc();

private:
    int pc_;
    JStack stack_;
};
}
#endif /* ifndef  */
