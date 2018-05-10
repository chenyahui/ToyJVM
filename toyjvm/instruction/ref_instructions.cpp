//
// Created by cyhone on 18-4-24.
//

#include <toyjvm/instruction/ref_instructions.h>
#include <toyjvm/runtime/jvm_thread.h>

namespace jvm {
    void NEW_Instruction::execute(jvm::JvmFrame &frame)
    {
        const auto &rt_const_pool = frame.method()->klass()->runtimeConstPool();
        auto class_ref = rt_const_pool.at<ClassRef *>(this->operand_);
        auto klass = class_ref->resolveClass();
        auto obj = new JvmObject(klass);
        frame.operandStack().push(obj);
    }


    void CHECKCAST_Instruction::execute(jvm::JvmFrame &frame)
    {
        auto &opstack = frame.operandStack();
        auto obj_ref = opstack.pop<std::shared_ptr<JvmRef>>();

        if (obj_ref == nullptr) {
            return;
        }
        auto tclass = frame.method()
                ->klass()
                ->runtimeConstPool().at<ClassRef *>(this->operand_)
                ->resolveClass();

        if (!obj_ref->isInstanceOf(tclass)) {
            // todo throw exception
        }
    }

    void INSTANCEOF_Instruction::execute(jvm::JvmFrame &frame)
    {
        auto &opstack = frame.operandStack();
        auto obj_ref = opstack.pop<std::shared_ptr<JvmRef>>();

        if (obj_ref == nullptr) {
            opstack.push<int>(0);
            return;
        }

        auto tclass = frame.method()
                ->klass()
                ->runtimeConstPool().at<ClassRef *>(this->operand_)
                ->resolveClass();

        opstack.push<int>(obj_ref->isInstanceOf(tclass));
    }

    void ATHROW_Instruction::execute(jvm::JvmFrame &frame)
    {
        auto ex_obj = frame.operandStack().pop<jobj>();

        if (ex_obj == nullptr) {
            throw "null pointer";
        }

        auto &the_thread = frame.thread();
        if (!findAndGotoExceptionHandler(the_thread, ex_obj)) {
            handleUncaughtException(the_thread, ex_obj);
        }
    }

    bool ATHROW_Instruction::findAndGotoExceptionHandler(jvm::JvmThread &jthread, jvm::JvmObject *obj)
    {
        while (true) {
            auto frame = jthread.top();
            auto pc = frame->nextPc() - 1;

            auto handler_pc = frame
                    ->method()
                    ->findExceptionHandler(dynamic_cast<JvmClass *>(obj->klass()), pc);
            if (handler_pc > 0) {
                auto &opstack = frame->operandStack();
                opstack.clear();
                opstack.push<jobj>(obj);
                frame->setNextPc(handler_pc);
                return true;
            }
            jthread.pop();
            if (jthread.empty()) {
                break;
            }
        }

        return false;
    }

    void ATHROW_Instruction::handleUncaughtException(jvm::JvmThread &jthread, jvm::JvmObject *exobj)
    {
        jthread.clear();
        auto msg_obj = dynamic_cast<jobj>(exobj->getRef("detailMessage", "Ljava/lang/String;"));

        std::string msg = javaLangStringAsString(msg_obj);
        std::cout << "Exception in thread \"main\" " << exobj->klass()->name() << ":" << msg << std::endl;
        if (exobj->hasExtra()) {
            auto stack_traces = exobj->getExtra<std::vector<StackTraceElement>>();

            for (auto &trace_item : stack_traces) {
                std::cout << "\t at " << trace_item.ToString() << std::endl;
            }
        }
    }
}