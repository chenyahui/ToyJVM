//
// Created by cyhone on 17-3-13.
//
#pragma once

#include <classfile/attributeinfo.h>
#include <classfile/attr_code.h>
#include <classfile/attr_constant_value.h>
#include <classfile/attr_markers.h>
#include <classfile/attr_exceptions.h>
#include <classfile/attr_line_number_table.h>
#include <classfile/attr_local_variable_table.h>
#include <classfile/attr_source_file.h>
#include <classfile/attr_unparsed.h>

namespace cyh {
    AttributeInfo_ptrs readAttributes(ClassReader reader, ConstantPool cp) {
        uint16 attributeCount = reader.readUint16();
        AttributeInfo_ptrs attributeInfos = AttributeInfo_ptrs(attributeCount);

        for (auto i = 0; i < attributeCount; ++i) {
            attributeInfos[i] = readAttribute(reader, cp);
        }
    }

    AttributeInfo *readAttribute(ClassReader reader, ConstantPool cp) {
        auto attrNameIndex = reader.readUint16();
        auto attrName = cp.getUtf8(attrNameIndex);
        auto attrLen = reader.readUint32();
        AttributeInfo *attrInfo = newAttributeInfo(attrName, attrLen, cp);
        attrInfo->readInfo(reader);
        return attrInfo;
    }


    AttributeInfo *newAttributeInfo(std::string attrName,
                                    uint32 attrLen,
                                    ConstantPool cp) {
        if (attrName == "Code")
            return new CodeAttribute(cp);
        if (attrName == "ConstantValue")
            return new ConstantValueAttribute();
        if (attrName == "Deprecated")
            return new DeprecatedAttribute();
        if (attrName == "Exceptions")
            return new ExceptionsAttribute();
        if (attrName == "LineNumberTable")
            return new LineNumberTableAttribute();
        if (attrName == "LocalVariableTable")
            return new LocalVariableTableAttribute();
        if (attrName == "SourceFile")
            return new SourceFileAttribute(cp);
        if (attrName == "Synthetic")
            return new SyntheticAttribute();
        return new UnparsedAttribute(attrName, attrLen, nullptr);

    }
}
