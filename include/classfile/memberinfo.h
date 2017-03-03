#pragma once

#include <vector>
#include "attributeinfo.h"
#include "constantPool.h"


namespace cyh {
    using MemberInfos = std::vector<MemberInfo>;

    class MemberInfo {
    public:
        MemberInfo(ConstantPool _cp, uint16 _af, uint16 _ni, uint16 _di, std::vector<AttributeInfo> _attrs) :
                cp(_cp), accessFlags(_af), nameIndex(_ni), descriptorIndex(_di), attributes(_attrs) {

        }

    private:
        ConstantPool cp;
        uint16 accessFlags;
        uint16 nameIndex;
        uint16 descriptorIndex;
        std::vector<AttributeInfo> attributes;

    };

    MemberInfo readMember(ClassReader reader, ConstantPool cp);

    std::vector<MemberInfo> readMembers(ClassReader reader, ConstantPool cp);
}
