#ifndef MY_JVM_RTDATA_JVM_FRAME_H
#define MY_JVM_RTDATA_JVM_FRAME_H

#include <jvm/rtdata/local_vars.h>
#include <jvm/rtdata/operand_stack.h>
#include <jvm/rtdata/jvm_thread.h>

namespace cyh {
class JFrame {
public:
    OperandStack& OpStack();
    LocalVarRefs& LocalVars();
    JThread*  Thread();
private:
    LocalVarRefs local_var_or_ref_;
    OperandStack operand_stack_;
    JThread* current_thread_;
};
}

#endif
