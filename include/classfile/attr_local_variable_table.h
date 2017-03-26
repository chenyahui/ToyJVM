#pragma once

#include <types.h>
#include "attributeinfo.h"

namespace cyh {
    using LocalVariableTableEntrys = std::vector<LocalVariableTableEntry>;

    class LocalVariableTableAttribute : public AttributeInfo {
    private:
        LocalVariableTableEntrys localVariableTable;
    public:
        void readInfo(ClassReader reader) override;

    };

    struct LocalVariableTableEntry {
        uint16 startPc;
        uint16 length;
        uint16 nameIndex;
        uint16 descriptorIndex;
        uint16 index;
    };
}
