#include <jvm/classfile/attribute_infos.h>
namespace cyh {
void AttributeConstantValueInfo::ReadInfo(ClassReader& reader)
{
    constant_value_index_ = reader.ReadU2();
}

void AttributeCodeInfo::ReadInfo(ClassReader& reader)
{
    max_stack_ = reader.ReadU2();
    max_locals_ = reader.ReadU2();

    u4 code_num = reader.ReadU4();
    code_ = reader.ReadU1s(code_num);

    auto exception_len = reader.ReadU2();
    exception_table_.reserve(exception_len);
    for (int i = 0; i < exception_len; ++i) {
	ExceptionInfo e;
	e.start_pc = reader.ReadU2();
	e.end_pc = reader.ReadU2();
	e.handler_pc = reader.ReadU2();
	e.catch_type = reader.ReadU2();

	exception_table_.push_back(e);
    }

    attribute_table_.Read(reader, pool_);
}

void AttributeExceptionsInfo::ReadInfo(ClassReader& reader)
{
    exception_index_table_ = reader.ReadU2s();
}

void AttributeInnerClassesInfo::ReadInfo(ClassReader& reader)
{
    u2 class_num = reader.ReadU2();
    inner_classes_.reserve(class_num);
    for (int i = 0; i < class_num; ++i) {
	InnerClassInfo c;
	c.inner_class_info_index = reader.ReadU2();
	c.outer_class_info_index = reader.ReadU2();
	c.inner_name_index = reader.ReadU2();
	c.inner_class_access_flags = reader.ReadU2();

	inner_classes_.push_back(c);
    }
}

void AttributeEnclosingMethodInfo::ReadInfo(ClassReader& reader)
{
    class_index_ = reader.ReadU2();
    method_index_ = reader.ReadU2();
}

void AttributeSignatureInfo::ReadInfo(ClassReader& reader)
{
    signature_index_ = reader.ReadU2();
}

void AttributeSourceFileInfo::ReadInfo(ClassReader& reader)
{
    sourcefile_index_ = reader.ReadU2();
}

void AttributeLineNumberTableInfo::ReadInfo(ClassReader& reader)
{
    auto table_len = reader.ReadU2();
    line_number_table_.reserve(table_len);

    for (int i = 0; i < table_len; ++i) {
	LineNumberInfo l;
	l.start_pc = reader.ReadU2();
	l.line_number = reader.ReadU2();

	line_number_table_.push_back(l);
    }
}
void AttributeLocalVariableTableInfo::ReadInfo(ClassReader& reader)
{
    auto count = reader.ReadU2();
    for (int i = 0; i < count; ++i) {
	LocalVariableInfo item;
	item.start_pc = reader.ReadU2();
	item.length = reader.ReadU2();
	item.name_index = reader.ReadU2();
	item.descriptor_index = reader.ReadU2();
	item.index = reader.ReadU2();
	local_variable_table_.push_back(item);
    }
}
void AttributeLocalVariableTypeTableInfo::ReadInfo(ClassReader& reader)
{
    auto count = reader.ReadU2();
    for (int i = 0; i < count; ++i) {
	LocalVariableTypeInfo item;
	item.start_pc = reader.ReadU2();
	item.length = reader.ReadU2();
	item.name_index = reader.ReadU2();
	item.signature_index = reader.ReadU2();
	item.index = reader.ReadU2();
	local_variable_type_table_.push_back(item);
    }
}

void AttributeUnparsedInfo::ReadInfo(ClassReader& reader)
{
    data_ = reader.ReadU1s(attr_len_);
}

void AttributeBootstrapMethodsInfo::ReadInfo(ClassReader& reader)
{
    auto count = reader.ReadU2();
    for (int i = 0; i < count; ++i) {
	BootStrapMethod item;
	item.bootstrap_method_ref = reader.ReadU2();
	item.bootstrap_arguments = reader.ReadU2s();
	bootStrap_methods_.push_back(item);
    }
}
}
