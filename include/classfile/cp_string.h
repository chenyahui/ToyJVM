#pragma once

//
// Created by cyhone on 17-3-3.
//
#include "constantPool.h"

namespace cyh {
    class ConstantStringInfo : public ConstantInfo {
    public:
        ConstantStringInfo(ConstantPool _cp) : cp(_cp) {}

        void readInfo(ClassReader reader) override;

        std::string String();

    private:
        ConstantPool cp;
        uint16 stringIndex;
    };
}
