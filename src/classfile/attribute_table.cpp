#include <jvm/classfile/attribute_infos.h>
#include <jvm/classfile/attribute_table.h>

namespace cyh {

void AttributeTable::Read(ClassReader& reader, ConstantPool* pool)
{
    u2 count = reader.ReadU2();
    attributes_infos_.reserve(count);

    for (int i = 0; i < count; ++i) {
	auto attr_info = ReadAttributeInfo(reader, pool);
	attr_info->ReadInfo(reader);
	attributes_infos_.push_back(attr_info);
    }
}

AttributeInfo* AttributeTable::ReadAttributeInfo(ClassReader& reader, ConstantPool* pool)
{
    u2 attr_name_index = reader.ReadU2();
    u4 attr_len = reader.ReadU4();
    std::string attr_name = pool->GetUtf8AsString(attr_name_index);

    AttributeInfo* attr_info = NewAttributeInfo(attr_name, pool);
    if (attr_info == NULL) {
	return new AttributeUnparsedInfo(attr_name, attr_len);
    }
    return attr_info;
}

AttributeInfo* AttributeTable::NewAttributeInfo(std::string attr_name, ConstantPool* pool)
{
    if (attr_name == "BootstrapMethods") {
	return new AttributeBootstrapMethodsInfo();
    } else if (attr_name == "Code") {
	return new AttributeCodeInfo(pool);
    } else if (attr_name == "ConstantValue") {
	return new AttributeConstantValueInfo();
    } else if (attr_name == "Deprecated") {
	return new AttributeDeprecatedInfo();
    } else if (attr_name == "EnclosingMethod") {
	return new AttributeEnclosingMethodInfo();
    } else if (attr_name == "Exceptions") {
	return new AttributeExceptionsInfo();
    } else if (attr_name == "InnerClasses") {
	return new AttributeInnerClassesInfo();
    } else if (attr_name == "LineNumberTable") {
	return new AttributeLineNumberTableInfo();
    } else if (attr_name == "LocalVariableTable") {
	return new AttributeLocalVariableTableInfo();
    } else if (attr_name == "LocalVariableTypeTable") {
	return new AttributeLocalVariableTypeTableInfo();
    } else if (attr_name == "Signature") {
	return new AttributeSignatureInfo();
    } else if (attr_name == "SourceFile") {
	return new AttributeSourceFileInfo(pool);
    } else if (attr_name == "Synthetic") {
	return new AttributeSyntheticInfo<>();
    }

    return NULL;
}
}
