//
// Created by cyhone on 17-3-26.
//
#include <classfile/attr_line_number_table.h>

namespace cyh {
    int LineNumberTableAttribute::GetLineNumber(int pc) {
        for (int i = lineNumberTable.size(); i >= 0; --i) {
            auto entry = lineNumberTable[i];
            if (pc > int(entry.startPc)) {
                return int(entry.lineNumber);
            }
        }
        return -1;
    }

    void LineNumberTableAttribute::readInfo(ClassReader reader) {
        auto lineNumberTableLength = reader.readUint16();
        lineNumberTable = LineNumberTableEntrys(lineNumberTableLength);
        for (int i = 0; i < lineNumberTableLength; ++i) {
            lineNumberTable[i] = LineNumberTableEntry(reader.readUint16(),
                                                      reader.readUint16());
        }
    }
}