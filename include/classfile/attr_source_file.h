#pragma once

#include "constantPool.h"
#include "attributeinfo.h"

namespace cyh {
    class SourceFileAttribute : public AttributeInfo {
    private:
        ConstantPool cp;
        uint16 sourceFileIndex;
    public:
        SourceFileAttribute(ConstantPool _cp);

        void readInfo(ClassReader reader) override;

        std::string filename();
    };
}
