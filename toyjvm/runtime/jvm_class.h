//
// Created by cyhone on 2018/3/9.
//

#ifndef TOYJVM_JVM_CLASS_H
#define TOYJVM_JVM_CLASS_H

#include <boost/core/noncopyable.hpp>
#include <toyjvm/classfile/classfile.h>
namespace jvm {
    class Vtable;

    class JvmClass : boost::noncopyable {
    private:
        Vtable *vtable_;
    };
}
#endif //TOYJVM_JVM_CLASS_H
