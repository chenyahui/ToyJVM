//
// Created by cyhone on 18-5-8.
//
#include<toyjvm/native/java/lang/System.h>

using namespace jvm::native;


void JavaLangSystem::registerMethod(const std::string &method_name, const std::string &method_descriptor,
                                    jvm::native::NativeMethod native_method)
{
    NativeMethods::registerMethod("java/lang/System", method_name, method_descriptor, native_method);
}

bool JavaLangSystem::init()
{
    registerMethod("arraycopy",
                   "(Ljava/lang/Object;ILjava/lang/Object;II)V", BIND_STATIC(JavaLangSystem::arraycopy));
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

    if (!checkArrayCopy(src, dest)) {
        throw "array store exception";
    }

    if (src_pos < 0 || dest_pos < 0 || length < 0
        || src_pos + length > src->arrayLen()
        || dest_pos + length > dest->arrayLen()) {
        throw "index bounds exception";
    }

    switch (src->klass()->name()[1]) {
        case 'Z': {
            return realArrayCopy<bool>(src, dest, src_pos, dest_pos, length);
        }
        case 'B': {
            return realArrayCopy<jbyte>(src, dest, src_pos, dest_pos, length);
        }
        case 'C': {
            return realArrayCopy<jchar>(src, dest, src_pos, dest_pos, length);
        }
        case 'S': {
            return realArrayCopy<jshort>(src, dest, src_pos, dest_pos, length);
        }
        case 'I': {
            return realArrayCopy<jint>(src, dest, src_pos, dest_pos, length);
        }
        case 'J': {
            return realArrayCopy<jlong>(src, dest, src_pos, dest_pos, length);
        }
        case 'F': {
            return realArrayCopy<jfloat>(src, dest, src_pos, dest_pos, length);
        }
        case 'D': {
            return realArrayCopy<jdouble>(src, dest, src_pos, dest_pos, length);
        }
        case 'L': {
            return realArrayCopy<jref>(src, dest, src_pos, dest_pos, length);
        }
        default: {
            assert(false);
        }
    }
}

bool JavaLangSystem::checkArrayCopy(jvm::JvmBaseArray *src, jvm::JvmBaseArray *dest)
{
    auto src_class = src->klass();
    auto dest_class = dest->klass();

    if (!src_class->isArray() || !dest_class->isArray()) {
        return false;
    }

    auto src_arr_class = dynamic_cast<JvmArrayClass *>(src_class);
    auto dest_arr_class = dynamic_cast<JvmArrayClass *>(dest_class);

    assert(src_arr_class && dest_arr_class);

    if (src_arr_class->componentClass()->isPrimitive() && dest_arr_class->componentClass()->isPrimitive()) {
        return src_class == dest_class;
    }

    return true;
}