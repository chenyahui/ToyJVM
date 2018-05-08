//
// Created by cyhone on 18-5-6.
//
#include <toyjvm/instruction/invoke_instructions.h>
#include <toyjvm/runtime/jvm_thread.h>
#include <glog/logging.h>
#include <toyjvm/native/native_methods.h>

namespace jvm {
    void BaseInvokeInstruction::execute(jvm::JvmFrame &frame)
    {
        auto &const_pool = frame.method()->klass()->runtimeConstPool();
        method_ref_ = const_pool.at<MethodRef *>(index_);
        resolved_method_ = method_ref_->resolveMethod();

        current_class_ = frame.method()->klass();
        resolved_class_ = method_ref_->resolveClass();


        auto method_to_invoked = findMethodToInvoked(frame);
        if (method_to_invoked) {
            invokeMethod(frame, method_to_invoked);
        } else {
            DLOG(INFO) << "method to be invoked is null";
        }
    }

    void BaseInvokeInstruction::invokeMethod(jvm::JvmFrame &invoker, jvm::JvmMethod *method)
    {
        auto &thread = invoker.thread();
        auto new_frame = new JvmFrame(thread, method);
        thread.push(new_frame);

        auto &opstack = invoker.operandStack();
        auto &local_vars = new_frame->localSlots();

        for (int i = method->argsSlotCount() - 1; i >= 0; i--) {
            auto slot = opstack.pop<boost::any>();
            local_vars.set<boost::any>(i, slot);
        }
    }

    JvmMethod *INVOKESTATIC_Instruction::findMethodToInvoked(JvmFrame &frame)
    {
        // todo check is static
        return resolved_method_;
    }

    JvmMethod *INVOKESPECIAL_Instruction::findMethodToInvoked(JvmFrame &frame)
    {
        auto ref = frame.operandStack().getRefFromTop(resolved_method_->argsSlotCount());
        if (ref == nullptr) {
            // todo nullpointer exception
            assert(false);
        }

        auto method_to_invoked = resolved_method_;
        if (current_class_->accessFlags().isSuper()
            && current_class_->isSubClassOf(current_class_)
            && resolved_method_->name() != "<init>") {
            method_to_invoked = lookUpMethodInClass(current_class_->superClass(),
                                                    method_ref_->name(),
                                                    method_ref_->descriptor());
        }

        // todo check null or abstract

        return method_to_invoked;
    }

    static void _println(OperandStack &opstack, std::string &descriptor)
    {
        if (descriptor == "(J)V") {
            std::cout << opstack.pop<jlong>() << std::endl;
        } else if (descriptor == "(I)V") {
            std::cout << opstack.pop<jint>() << std::endl;
        } else if (descriptor == "(Ljava/lang/String;)V") {
//            auto str_obj = opstack.pop<jref>();
//            std::string str_raw = TransJString(str_obj);
//            std::cout << str_raw << std::endl;
            std::cout << "尚不支持的类型" << descriptor << std::endl;
        } else {
            std::cout << "尚不支持的类型" << descriptor << std::endl;
        }
        opstack.pop<jref>();
    }

    JvmMethod *INVOKEVIRTUAL_Instruction::findMethodToInvoked(jvm::JvmFrame &frame)
    {
        // todo check resolved_method is not static
        auto ref = frame.operandStack().getRefFromTop(resolved_method_->argsSlotCount());
        if (ref == nullptr) {
            // hack!

            // todo nullpointer exception
            assert(false);
        }

        // check access legality
        auto method_to_invoked = lookUpMethodInClass(current_class_->superClass(),
                                                     method_ref_->name(),
                                                     method_ref_->descriptor());
        // todo check null or abstract

        return method_to_invoked;
    }

    JvmMethod *INVOKEINTERFACE_Instruction::findMethodToInvoked(jvm::JvmFrame &frame)
    {
        // todo 校验合法性
        return lookUpMethodInClass(current_class_->superClass(),
                                   method_ref_->name(),
                                   method_ref_->descriptor());
    }

    void INVOKENATIVE_Instruction::execute(jvm::JvmFrame &frame)
    {
        auto method = frame.method();
        const auto &class_name = method->klass()->name();
        const auto &method_name = method->name();
        const auto &method_descriptor = method->descriptor();

        auto native_method = NativeMethods::find(class_name, method_name, method_descriptor);
        if (native_method == boost::none) {
            auto method_info = class_name + "." + method_name + method_descriptor;
            throw "INVOKE_NATIVE error" + method_info;
        }
        native_method.get()(frame);
    }

}
