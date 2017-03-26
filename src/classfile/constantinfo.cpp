//
// Created by cyhone on 17-3-3.
//

#include <classfile/constantinfo.h>
#include <classfile/cp_numeric.h>
#include <classfile/cp_utf8.h>
#include <classfile/cp_string.h>
#include <classfile/cp_class.h>
#include <classfile/cp_member_ref.h>
#include <classfile/cp_name_type.h>
#include <classfile/cp_invoke_dynamic.h>
#include <exception.h>

namespace cyh {
    ConstantInfo *newConstantInfo(Byte tag, ConstantPool cp) {
        switch (tag) {
            case INTEGER:
                return new ConstantIntegerInfo();
            case FLOAT:
                return new ConstantFloatInfo();
            case LONG:
                return new ConstantLongInfo();
            case DOUBLE:
                return new ConstantDoubleInfo();
            case UTF8:
                return new ConstantUtf8Info();
            case STRING:
                return new ConstantStringInfo(cp);
            case CLASS:
                return new ConstantClassInfo(cp);
            case FIELD_REF:
                return new ConstantFieldrefInfo(cp);
            case METHOD_REF:
                return new ConstantMethodrefInfo(cp);
            case INTERFACE_METHOD_REF:
                return new ConstantInterfaceMethodrefInfo(cp);
            case NAME_AND_TYPE:
                return new ConstantNameAndTypeInfo();
            case METHOD_TYPE:
                return new ConstantMethodTypeInfo();
            case METHOD_HANDLE:
                return new ConstantMethodHandleInfo();
            case INVOKE_DYNAMIC:
                return new ConstantInvokeDynamicInfo();
            default:
                throw ClassFormatError("java.lang.ClassFormatError: constant pool tag!");
        }
    }
}