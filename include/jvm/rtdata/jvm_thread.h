#ifndef MY_JVM_RTDATA_JVM_THREAD_H
#define MY_JVM_RTDATA_JVM_THREAD_H

#include <jvm/classfile/constant_pool.h>
#include <jvm/rtdata/jvm_frame.h>
#include <jvm/utils/unsafe.h>
#include <stack>
#include <vector>

namespace cyh {

using JStack = std::stack<JFrame*>;

class JThread {
public:
    inline void SetPc(int pc){pc_ = pc;}
    inline int Pc() { return pc_; }
    JFrame* PopFrame();
    void PushFrame(JFrame* frame);
    void NewAndPushFrame(int, int);
    JFrame* NewFrame(int, int);

private:
    int pc_;
    JStack stack_;
};
}
#endif /* ifndef  */
