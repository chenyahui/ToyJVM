//
// Created by cyhone on 17-3-3.
//



#include <classfile/classfile.h>
#include <exception.h>

namespace cyh {
    void ClassFile::readAndCheckMagic(ClassReader reader) {
        uint32 magic = reader.readUint32();
        if (magic != 0xCAFEBABE) {
            throw ClassFormatError("java.lang.ClassFormatError: magic");
        }
    }

    void ClassFile::readAndCheckVersion(ClassReader reader) {
        this->minorVersion = reader.readUint16();
        this->majorVersion = reader.readUint16();

        if (majorVersion == 45)
            return;
        if (majorVersion <= 52 && majorVersion >= 46) {
            if (minorVersion == 0) {
                return;
            }
        }
    }

    void ClassFile::read(ClassReader reader) {
        readAndCheckMagic(reader);
        readAndCheckVersion(reader);
        constantPool = readConstantPool(reader);
        accessFlags = reader.readUint16();
        thisClass = reader.readUint16();
        superClass = reader.readUint16();
        interfaces = reader.readUint16s();
        fields = readMembers(reader, constantPool);
        methods = readMembers(reader, constantPool);
        attributes = readAttributes(reader, constantPool);
    }
}