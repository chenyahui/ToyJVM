//
// Created by cyhone on 18-4-14.
//

#include <toyjvm/classfile/const_infos.h>

namespace jvm {
    void ConstClassInfo::read(jvm::BaseReader &reader)
    {
        name_index_ = reader.read<u2>();
    }
}