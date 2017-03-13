#pragma once

#include "constantinfo.h"

namespace cyh {
    class ConstantClassInfo : public ConstantInfo {
    public:
        ConstantClassInfo(ConstantPool _cp) : cp(_cp) {}

        void readInfo(ClassReader reader) override;

        std::string name();

        uint16 getNameIndex();

    private:
        ConstantPool cp;
        uint16 nameIndex;
    };
}