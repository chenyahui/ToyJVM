//
// Created by cyhone on 17-3-4.
//

#include <classfile/cp_utf8.h>

namespace cyh {
    void ConstantUtf8Info::readInfo(ClassReader reader) {
        auto length = (uint32) reader.readUint16();
        auto bytes = reader.readBytes(length);
        _str = decodeMUTF8(bytes);
    }

    std::string ConstantUtf8Info::str() {
        return _str;
    }

    std::string decodeMUTF8(Bytes bytes) {
        return std::string(bytes.begin(), bytes.end());
    }
}