//
// Created by cyhone on 17-3-13.
//

#include <classfile/cp_invoke_dynamic.h>

namespace cyh {
    void ConstantMethodTypeInfo::
    readInfo(ClassReader reader) {
        this->descriptorIndex = reader.readUint16();
    }

    void ConstantMethodHandleInfo::
    readInfo(ClassReader reader) {
        this->referenceKind = reader.readUint8();
        this->referenceIndex = reader.readUint16();
    }

    void ConstantInvokeDynamicInfo::
    readInfo(ClassReader reader) {
        this->bootstrapMethodAttrIndex = reader.readUint16();
        this->nameAndTypeIndex = reader.readUint16();
    }
}
