//
// Created by cyhone on 17-3-4.
//

#include <classfile/cp_class.h>

namespace cyh {
    void ConstantClassInfo::readInfo(ClassReader reader) {
        nameIndex = reader.readUint16();
    }

    std::string ConstantClassInfo::name() {
        return cp.getUtf8(nameIndex);
    }

    uint16 ConstantClassInfo::getNameIndex() {
        return nameIndex;
    }
}