#pragma once

#include <types.h>
#include "constantinfo.h"

namespace cyh {
    class ConstantMethodTypeInfo : public ConstantInfo {
    private:
        uint16 descriptorIndex;
    public:
        void readInfo(ClassReader reader) override;
    };

    class ConstantMethodHandleInfo : public ConstantInfo {
    private:
        Byte referenceKind;
        uint16 referenceIndex;
    public:
        void readInfo(ClassReader reader) override;
    };

    class ConstantInvokeDynamicInfo : public ConstantInfo {
    private:
        uint16 bootstrapMethodAttrIndex;
        uint16 nameAndTypeIndex;
    public:
        void readInfo(ClassReader reader) override;
    };
}