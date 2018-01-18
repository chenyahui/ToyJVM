#ifndef TOYJVM_INTERPRET_H
#define TOYJVM_INTERPRET_H
#include <jvm/instruction/base_instruction.h>
#include <jvm/rtdata/jvm_class.h>
#include <jvm/rtdata/jvm_frame.h>
#include <jvm/rtdata/jvm_member.h>
#include <jvm/rtdata/jvm_thread.h>
#include <jvm/rtdata/local_vars.h>
#include <jvm/rtdata/operand_stack.h>
namespace cyh {

void printOpStack(OperandStack& opstack);
void printLocalVar(LocalVarRefs& localvars);
void interpret(JMethod* method);
void loop(JThread*);
void printFrame(int pc, Instruction* inst);
void log_frame(JFrame* frame);
JMethod* GetMainFunc(JClass* jclass);
void startJvm(std::string&);
}

#endif /* end of include guard: TOYJVM_INTERPRET_H */
