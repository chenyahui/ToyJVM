//
// Created by cyhone on 17-3-26.
//
#include <classfile/attr_source_file.h>

namespace cyh {
    void SourceFileAttribute::readInfo(ClassReader reader) {
        sourceFileIndex = reader.readUint16();
    }

    std::string SourceFileAttribute::filename() {
        return cp.getUtf8(sourceFileIndex);
    }

    SourceFileAttribute::SourceFileAttribute(ConstantPool _cp) {
        cp = _cp;
    }
}