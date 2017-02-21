package com.cyhone.classfile;

import com.cyhone.exception.ClassFileError;
import com.cyhone.exception.EnvCheckError;


/**
 * @author cyhone
 * @date 2017/2/20
 */
public class ClassFile {
    private short minorVersion;
    private short majorVersion;
    private ConstantPool constantPool;
    private short accessFlags;
    private short thisClass;
    private short superClass;
    private short[] interfaces;
    private MemberInfo[] fields;
    private MemberInfo[] methods;
    private AttributeInfo[] attributes;

    public void read(ClassReader reader) {
        readAndCheckMagic(reader);
        readAndCheckVersion(reader);
        this.constantPool = ConstantPool.readConstantPool(reader);
        this.accessFlags = reader.readShort();
        this.thisClass = reader.readShort();
        this.superClass = reader.readShort();
        this.interfaces = reader.readShorts();
        this.fields = MemberInfo.readMembers(reader, this.constantPool);
        this.methods = MemberInfo.readMembers(reader, this.constantPool);
        this.attributes = AttributeInfo.readAttributes(reader, this.constantPool);
    }

    private void readAndCheckMagic(ClassReader reader) {
        int magic = reader.readInt();
        if (magic != 0xCAFEBABE) {
            throw new ClassFileError("java.lang.ClassFormatError: magic!");
        }
    }

    private void readAndCheckVersion(ClassReader reader) {
        this.minorVersion = reader.readShort();
        this.majorVersion = reader.readShort();

        switch (majorVersion) {
            case 45:
                return;
            case 46:
            case 47:
            case 48:
            case 49:
            case 50:
            case 51:
            case 52:
                if (minorVersion == 0) {
                    return;
                }
        }
        throw new ClassFileError("java.lang.UnsupportedClassVersionError!");
    }
}
