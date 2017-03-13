
//
// Created by cyhone on 17-3-4.
//
#include <classfile/cp_member_ref.h>

namespace cyh {
    void ConstantMemberrefInfo::readInfo(ClassReader reader) {
        classIndex = reader.readUint16();
        nameAndTypeIndex = reader.readUint16();
    }

    std::string ConstantMemberrefInfo::ClassName() {
        return cp.getClassName(classIndex);
    }

    std::pair<std::string, std::string> ConstantMemberrefInfo::NameAndDescriptor() {
        return cp.getNameAndType(nameAndTypeIndex);
    }

    ConstantMemberrefInfo::ConstantMemberrefInfo(const ConstantPool &cp) : cp(cp) {}

}
