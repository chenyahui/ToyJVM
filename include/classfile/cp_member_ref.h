//
// Created by cyhone on 17-3-4.
//
#pragma once

#include "constantinfo.h"

namespace cyh {

    typedef ConstantMemberrefInfo ConstantFieldrefInfo;
    typedef ConstantMemberrefInfo ConstantMethodrefInfo;
    typedef ConstantMemberrefInfo ConstantInterfaceMethodrefInfo;

    class ConstantMemberrefInfo : public ConstantInfo {
    protected:
        ConstantPool cp;
        uint16 classIndex;
        uint16 nameAndTypeIndex;
    public:
        ConstantMemberrefInfo(const ConstantPool &cp);

        void readInfo(ClassReader reader) override;

        std::string ClassName();

        std::pair<std::string, std::string> NameAndDescriptor();
    };


}