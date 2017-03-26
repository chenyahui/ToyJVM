//
// Created by cyhone on 17-3-17.
//
#include <classfile/attr_exceptions.h>

namespace cyh {
    void ExceptionsAttribute::readInfo(ClassReader reader) {
        exceptionIndexTable = reader.readUint16s();
    }

    std::vector<uint16> ExceptionsAttribute::ExceptionIndexTable() {
        return exceptionIndexTable;
    }

}