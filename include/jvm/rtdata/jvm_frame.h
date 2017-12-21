#ifndef MY_JVM_RTDATA_JVM_FRAME_H
#define MY_JVM_RTDATA_JVM_FRAME_H

#include <jvm/rtdata/local_vars.h>
#include <jvm/rtdata/operand_stack.h>

namespace cyh {
class JThread;

class JFrame {
public:
    JFrame(JThread* thread, int max_locals, int max_stack)
	: local_var_or_ref_(max_locals)
	, operand_stack_(max_stack)
	, current_thread_(thread)
	, nextpc_(0)
    {
    }
    inline OperandStack& OpStack() {return operand_stack_;}
    inline LocalVarRefs& LocalVars() {return local_var_or_ref_;}
    inline JThread* Thread() {return current_thread_;}
    inline int NextPc() { return nextpc_; }
    inline void SetNextPc(int pc) { nextpc_ = pc; }

private:
    LocalVarRefs local_var_or_ref_;
    OperandStack operand_stack_;
    JThread* current_thread_;
    int nextpc_;
};
}

#endif
