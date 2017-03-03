//
// Created by cyhone on 17-3-3.
//
#pragma once

#include "constantinfo.h"

namespace cyh {
    class ConstantUtf8Info : public ConstantInfo {
    public:
        void readInfo(ClassReader reader) override;

        std::string str();

    private:
        std::string val;
    };

    std::string decodeMUTF8(Bytes bytes);
}
