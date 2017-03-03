//
// Created by cyhone on 17-3-3.
//

#include <classfile/memberinfo.h>
#include <classfile/constantPool.h>

namespace cyh {
    MemberInfos readMembers(ClassReader reader, ConstantPool cp) {
        uint16 membercount = reader.readUint16();
        MemberInfos members = MemberInfos(membercount);

        for (uint16 i = 0; i < membercount; ++i) {
            members[i] = readMember(reader, cp);
        }
        return members;
    }

    MemberInfo readMember(ClassReader reader, ConstantPool cp) {
        return MemberInfo(cp,
                          reader.readUint16(),
                          reader.readUint16(),
                          reader.readUint16(),
                          readAttributes(reader, cp));
    }
}