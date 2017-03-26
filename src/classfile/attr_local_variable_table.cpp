//
// Created by cyhone on 17-3-26.
//
#include <classfile/attr_local_variable_table.h>

namespace cyh {
    void LocalVariableTableAttribute::readInfo(ClassReader reader) {
        auto localVariableTableLength = reader.readUint16();
        localVariableTable = LocalVariableTableEntrys(localVariableTableLength);

        for (int i = 0; i < localVariableTableLength; ++i) {
            localVariableTable[i].startPc = reader.readUint16();
            localVariableTable[i].length = reader.readUint16();
            localVariableTable[i].nameIndex = reader.readUint16();
            localVariableTable[i].descriptorIndex = reader.readUint16();
            localVariableTable[i].index = reader.readUint16();
        }
    }
}