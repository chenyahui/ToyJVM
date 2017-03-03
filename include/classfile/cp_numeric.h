
#pragma once

#include "constantinfo.h"
//
// Created by cyhone on 17-3-3.
//
namespace cyh {
    class ConstantIntegerInfo : public ConstantInfo {
    public:
        void readInfo(ClassReader reader) override;

        int32_t value();

    private:
        int32_t val;
    };
}

namespace cyh {
    class ConstantFloatInfo : public ConstantInfo {
    public:
        void readInfo(ClassReader reader) override;

        float value();

    private:
        float val;
    };
}

namespace cyh {
    class ConstantLongInfo : public ConstantInfo {
    public:
        void readInfo(ClassReader reader) override;

        long value();

    private:
        long val;
    };
}

namespace cyh{
    class ConstantDoubleInfo : public ConstantInfo {
    public:
        void readInfo(ClassReader reader) override;

        double value();
    private:
        double val;
    };
}
