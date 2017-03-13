#pragma once

#include "classreader.h"


namespace cyh {
    class ConstantInfo;

    class ConstantPool {
    public:
        ConstantInfo *getConstantInfo(uint16 index);

        std::string getUtf8(uint16 index);

        std::string getClassName(uint16 index);

        std::pair<std::string, std::string> getNameAndType(uint16 index);

    private:
        std::vector<ConstantInfo *> constantInfos;
    };

    ConstantPool readConstantPool(ClassReader reader);
}
