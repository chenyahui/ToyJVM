#pragma once

#include "attributeinfo.h"

namespace cyh {
    using LineNumberTableEntrys = std::vector<LineNumberTableEntry>;

    class LineNumberTableAttribute : public AttributeInfo {
    private:
        LineNumberTableEntrys lineNumberTable;
    public:
        int GetLineNumber(int pc);

        void readInfo(ClassReader reader) override;
    };

    struct LineNumberTableEntry {
        uint16 startPc;
        uint16 lineNumber;

        LineNumberTableEntry(uint16 _startPc, uint16 _lineNumber) {
            startPc = _startPc;
            lineNumber = _lineNumber;
        }

    };
}
