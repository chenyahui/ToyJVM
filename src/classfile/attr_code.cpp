//
// Created by cyhone on 17-3-13.
//

#include <classfile/attr_code.h>

namespace cyh {
    CodeAttribute::
    CodeAttribute(ConstantPool _cp) : cp(_cp) {}

    void CodeAttribute::readInfo(ClassReader reader) {
        maxStack = reader.readUint16();
        maxLocals = reader.readUint16();
        uint32 codeLength : = reader.readUint32();
        code = reader.readBytes(codeLength);
        exceptionTable = readExceptionTable(reader);
        attributes = readAttributes(reader, cp);
    }

    ExceptionTableEntrys readExceptionTable(ClassReader reader) {
        auto exceptionTableLength : = reader.readUint16();
        auto exceptionTable = ExceptionTableEntrys(exceptionTableLength);
        for (auto i = 0; i < exceptionTableLength; ++i) {
            exceptionTable[i] = ExceptionTableEntry(reader.readUint16(),
                                                    reader.readUint16(),
                                                    reader.readUint16(),
                                                    reader.readUint16());
        }
        return exceptionTable;
    }

    ExceptionTableEntry::
    ExceptionTableEntry(uint16 _startPc, uint16 _endPc, uint16 _handlerPc, uint16 _catchType) :
            startPc(_startPc), endPc(_endPc), handlerPc(_handlerPc), catchType(_catchType) {}
}