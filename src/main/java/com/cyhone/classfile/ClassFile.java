package com.cyhone.classfile;

import com.cyhone.exception.ClassFileError;
import com.cyhone.exception.EnvCheckError;
import com.cyhone.types.Uint16;

/**
 * @author cyhone
 * @date 2017/2/20
 */
public class ClassFile {
    private Uint16 minorVersion;
    private Uint16 majorVersion;
    private ConstantPool constantPool;
    private Uint16 accessFlags;
    private Uint16 thisClass;
    private Uint16 superClass;
    private Uint16[] interfaces;
    private MemberInfo[] fields;
    private MemberInfo[] methods;
    private AttributeInfo[] attributes;

    void read(ClassReader reader) {
        readAndCheckMagic(reader);
        readAndCheckVersion(reader);
        this.constantPool = ConstantPool.readConstantPool(reader);
        this.accessFlags = reader.readUint16();
        this.thisClass = reader.readUint16();
        this.superClass = reader.readUint16();
        this.interfaces = reader.readUint16s();
        this.fields = MemberInfo.readMembers(reader, this.constantPool);
        this.methods = MemberInfo.readMembers(reader, this.constantPool);
        this.attributes = AttributeInfo.readAttributes(reader, this.constantPool);
    }

    void readAndCheckMagic(ClassReader reader) {
        int magic = reader.readUint32().toInt();
        if (magic != 0xCAFEBABE) {
            throw new ClassFileError("java.lang.ClassFormatError: magic!");
        }
    }

    void readAndCheckVersion(ClassReader reader) {
        this.minorVersion = reader.readUint16();
        this.majorVersion = reader.readUint16();

        switch (majorVersion.toInt()) {
            case 45:
                return;
            case 46:
            case 47:
            case 48:
            case 49:
            case 50:
            case 51:
            case 52:
                if (minorVersion.toInt() == 0) {
                    return;
                }
        }
        throw new ClassFileError("java.lang.UnsupportedClassVersionError!");
    }
}
