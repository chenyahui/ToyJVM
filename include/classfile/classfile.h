#pragma once

#include <array>
#include <vector>
#include <types.h>
#include "constantPool.h"
#include "memberinfo.h"
#include "attributeinfo.h"
#include "classreader.h"

namespace cyh {
    class ClassFile {

    public:
        void read(ClassReader classReader);

    private:
        void readAndCheckMagic(ClassReader);

        void readAndCheckVersion(ClassReader);

        uint16 minorVersion;
        uint16 majorVersion;
        ConstantPool constantPool;
        uint16 accessFlags;
        uint16 thisClass;
        uint16 superClass;
        std::vector<uint16> interfaces;
        std::vector<MemberInfo> fields;
        std::vector<MemberInfo> methods;
        std::vector<AttributeInfo> attributes;
    };
}
