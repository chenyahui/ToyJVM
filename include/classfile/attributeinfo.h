#pragma once


#include <vector>
#include "classreader.h"
#include "constantPool.h"

namespace cyh {
    using AttributeInfo_ptrs = std::vector<AttributeInfo*>;

    class AttributeInfo {
    public:
        virtual void readInfo(ClassReader reader) = 0;
    };

    AttributeInfo_ptrs readAttributes(ClassReader reader, ConstantPool cp);

    AttributeInfo* readAttribute(ClassReader reader, ConstantPool cp);

    AttributeInfo *newAttributeInfo(std::string attrName,
                                    uint32 attrLen,
                                    ConstantPool cp);
}
