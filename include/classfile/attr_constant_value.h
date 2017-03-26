#pragma once

#include "attributeinfo.h"

namespace cyh {
    class ConstantValueAttribute : public AttributeInfo {
    private:
        uint16 constantValueIndex;
    public:
        uint16 ConstantValueIndex();

        void readInfo(ClassReader reader) override;
    };
}