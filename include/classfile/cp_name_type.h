#pragma  once

#include "constantinfo.h"

namespace cyh {
    class ConstantNameAndTypeInfo : public ConstantInfo {
    public:
        void readInfo(ClassReader reader) override;

        uint16 nameIndex;
        uint16 descriptorIndex;
    };

}