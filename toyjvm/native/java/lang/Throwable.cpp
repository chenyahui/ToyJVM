//
// Created by cyhone on 18-5-10.
//

#include <toyjvm/native/java/lang/Throwable.h>
#include <toyjvm/runtime/jvm_thread.h>

using namespace jvm::native;

void JavaLangThrowable::fillInStackTrace(jvm::JvmFrame &frame)
{
    auto this_obj = dynamic_cast<jobj>(frame.localSlots().getThis());

    frame.operandStack().push<jobj>(this_obj);
    auto stack_traces = createStackTraceElements(this_obj, frame.thread());
    this_obj->setExtra(stack_traces);
}

std::vector<jvm::StackTraceElement>
JavaLangThrowable::createStackTraceElements(jvm::JvmObject *obj, jvm::JvmThread &jthread)
{
    auto skip = distanceToObject(dynamic_cast<JvmClass *>(obj->klass())) + 2;
    auto &frame_vec = jthread.frames();

    std::vector<StackTraceElement> result;

    for (int i = skip; i < frame_vec.size(); ++i) {
        result.push_back(createStackTraceElement(frame_vec[i]));
    }
    return result;
}

jvm::StackTraceElement JavaLangThrowable::createStackTraceElement(jvm::JvmFrame *frame)
{
    auto method = frame->method();
    auto klass = dynamic_cast<JvmClass*>(method->klass());

    return {
            klass->sourceFileName(),
            klass->javaName(),
            method->name(),
            method->GetLineNumber(frame->NextPc() - 1)
    };
}

size_t JavaLangThrowable::distanceToObject(jvm::JvmClass *klass)
{
    size_t distance = 0;
    for (auto c = klass->superClass(); c != nullptr; c = c->superClass()) {
        distance++;
    }
    return distance;
}