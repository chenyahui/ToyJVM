//
// Created by cyhone on 17-3-17.
//
#include <classfile/attr_constant_value.h>

namespace cyh {
    uint16 ConstantValueAttribute::ConstantValueIndex() {
        return constantValueIndex;
    }

    void ConstantValueAttribute::readInfo(ClassReader reader) {
        constantValueIndex = reader.readUint16();
    }
}

