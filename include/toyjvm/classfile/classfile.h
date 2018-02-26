//
// Created by cyhone on 18-1-30.
//

#ifndef NEWJVM_CLASSFILE_H
#define NEWJVM_CLASSFILE_H

#include "toyjvm/common/uncopyable.h"
#include "toyjvm/base/const_pool.h"
#include <toyjvm/common/jvm_types.h>
#include <vector>

namespace jvm {
    class ClassFile : UnCopyable {
    public:
        ClassFile()
        {}

        void Parse(bytes);

    private:
        ConstPool const_pool_;
        u2 access_flags_;
        u2 this_class_;
        u2 super_class_;
        std::vector<u2> interfaces;
    };
}


#endif //NEWJVM_CLASSFILE_H
