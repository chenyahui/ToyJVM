//
// Created by cyhone on 17-3-4.
//

#include <classfile/cp_string.h>

namespace cyh {
    void ConstantStringInfo::readInfo(ClassReader reader) {
        stringIndex = reader.readUint16();
    }

    std::string ConstantStringInfo::String() {
        return cp.getUtf8(stringIndex);
    }
}