//
// Created by cyhone on 18-5-8.
//
#include<toyjvm/native/java/lang/System.h>

#include <toyjvm/native/native_methods.h>

using namespace jvm::native;

bool JavaLangSystem::init()
{
    NativeMethods::registerMethod("java/lang/System",
                                  "arraycopy",
                                  "(Ljava/lang/Object;ILjava/lang/Object;II)V",
                                  std::bind(JavaLangSystem::arraycopy,
                                            std::placeholders::_1));
    return true;
}

void JavaLangSystem::arraycopy(jvm::JvmFrame &frame)
{
    auto &local_vars = frame.localSlots();

    auto src = local_vars.at<JvmBaseArray *>(0);
    auto src_pos = local_vars.at<int>(1);

    auto dest = local_vars.at<JvmBaseArray *>(2);
    auto dest_pos = local_vars.at<int>(3);

    auto length = local_vars.at<int>(4);

    if (src == nullptr || dest == nullptr) {
        throw "array copy null pointer";
    }


}
