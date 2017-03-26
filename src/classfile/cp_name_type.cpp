//
// Created by cyhone on 17-3-13.
//
#include <classfile/cp_name_type.h>

namespace cyh {
    void ConstantNameAndTypeInfo::
    readInfo(ClassReader reader) {
        this->nameIndex = reader.readUint8();
        this->descriptorIndex = reader.readUint16();
    }
}