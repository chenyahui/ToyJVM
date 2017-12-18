#ifndef MY_JVM_RTDATA_JVM_THREAD_H
#define MY_JVM_RTDATA_JVM_THREAD_H

#include <jvm/classfile/constant_pool.h>
#include <jvm/rtdata/local_vars.h>
#include <jvm/rtdata/operand_stack.h>
#include <jvm/utils/unsafe.h>
#include <stack>
#include <vector>

namespace cyh {
class JFrame {
public:
    OperandStack& OpStack();
    LocalVarRefs& LocalVars();

private:
    LocalVarRefs local_var_or_ref_;
    OperandStack operand_stack_;
    ConstantPool* pool_;
};

using JStack = std::stack<JFrame*>;

class JThread {

private:
    int pc_;
    JStack stack_;
};
}
#endif /* ifndef  */
