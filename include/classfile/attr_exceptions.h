#pragma once

#include "attributeinfo.h"
namespace cyh {

    class ExceptionsAttribute : public AttributeInfo {
    private:
        std::vector<uint16> exceptionIndexTable;
    public:
        std::vector<uint16> ExceptionIndexTable();
        void readInfo(ClassReader reader) override;
    };
}
