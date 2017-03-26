//
// Created by cyhone on 17-3-26.
//

#include <classfile/attr_unparsed.h>

namespace cyh {
    void UnparsedAttribute::readInfo(ClassReader reader) {
        info = reader.readBytes(length);
    }

    Bytes UnparsedAttribute::Info() {
        return info;
    }

    UnparsedAttribute::UnparsedAttribute(std::string _name, uint32 _length, Bytes _info) :
            name(_name), length(_length), info(_info) {
    }
}