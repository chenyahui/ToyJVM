//
// Created by cyhone on 17-3-4.
//
#include <exception.h>
#include <classfile/constantPool.h>
#include <classfile/cp_utf8.h>
#include <classfile/cp_class.h>
#include <classfile/cp_name_type.h>

namespace cyh {
    ConstantInfo *ConstantPool::getConstantInfo(uint16 index) {
        if (index >= constantInfos.size()) {
            throw ClassFormatError("invalid constant pool index:" + index);
        }

        return constantInfos[index];
    }

    std::string ConstantPool::getUtf8(uint16 index) {
        return ((ConstantUtf8Info *) getConstantInfo(index))->str();
    }

    std::string ConstantPool::getClassName(uint16 index) {
        auto classInfo = (ConstantClassInfo *) getConstantInfo(index);
        return getUtf8(classInfo->getNameIndex());
    }

    std::pair<std::string, std::string> ConstantPool::getNameAndType(uint16 index) {
        auto ntInfo = (ConstantNameAndTypeInfo *) getConstantInfo(index);
        auto name = getUtf8(ntInfo->nameIndex);
        auto type = getUtf8(ntInfo->descriptorIndex);
        return std::make_pair(name, type);
    }

}