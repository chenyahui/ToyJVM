#pragma once

#include "attributeinfo.h"

namespace cyh {
    typedef MarkerAttribute DeprecatedAttribute;
    typedef MarkerAttribute SyntheticAttribute;

    class MarkerAttribute : public AttributeInfo {
    public:
        void readInfo(ClassReader reader) override;
    };
}