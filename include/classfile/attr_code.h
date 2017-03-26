//
// Created by cyhone on 17-3-13.
//
#pragma  once

#include "attributeinfo.h"

namespace cyh {
    using ExceptionTableEntrys = std::vector<ExceptionTableEntry>;

    class CodeAttribute : public AttributeInfo {
    private:
        ConstantPool cp;
        uint16 maxStack;
        uint16 maxLocals;
        Bytes code;
        ExceptionTableEntrys exceptionTable;
        AttributeInfo_ptrs attributes;
    public:
        CodeAttribute(ConstantPool cp);

        void readInfo(ClassReader reader) override;
    };


    class ExceptionTableEntry {
    public:
        uint16 startPc;
        uint16 endPc;
        uint16 handlerPc;
        uint16 catchType;

        ExceptionTableEntry(uint16, uint16, uint16, uint16);
    };

    ExceptionTableEntrys readExceptionTable(ClassReader reader);
}
