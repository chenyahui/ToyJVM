#ifndef MY_JVM_CLASSFILE_ATTRIBUTE_INFO_H
#define MY_JVM_CLASSFILE_ATTRIBUTE_INFO_H

#include <jvm/classfile/attribute_table.h>
#include <jvm/classfile/classreader.h>

namespace cyh {

class AttributeConstantValueInfo : public AttributeInfo {
public:
    AttributeConstantValueInfo()
	: AttributeInfo("ConstantValue")
    {
    }
    void ReadInfo(ClassReader&) override;
    inline u2 constant_value_index()
    {
	return constant_value_index_;
    }

private:
    u2 constant_value_index_; // must be a constant_pool index
};

struct ExceptionInfo {
    u2 start_pc;
    u2 end_pc;
    u2 handler_pc;
    u2 catch_type;
};

class AttributeCodeInfo : public AttributeInfo {
public:
    AttributeCodeInfo(ConstantPool* pool)
	: AttributeInfo("Code")
	, pool_(pool)
    {
    }
    void ReadInfo(ClassReader&) override;

public:
    u2 max_stack_;
    u2 max_locals_;
    bytes code_;
    std::vector<ExceptionInfo> exception_table_;
    AttributeTable attribute_table_;

    ConstantPool* pool_;
};

class AttributeExceptionsInfo : public AttributeInfo {
public:
    AttributeExceptionsInfo()
	: AttributeInfo("Exceptions")
    {
    }
    void ReadInfo(ClassReader& reader) override;

private:
    std::vector<u2> exception_index_table_;
};

struct InnerClassInfo {
    u2 inner_class_info_index;
    u2 outer_class_info_index;
    u2 inner_name_index;
    u2 inner_class_access_flags;
};
class AttributeInnerClassesInfo : public AttributeInfo {
public:
    AttributeInnerClassesInfo()
	: AttributeInfo("InnerClasses")
    {
    }
    void ReadInfo(ClassReader& reader) override;

private:
    std::vector<InnerClassInfo> inner_classes_;
};

class AttributeEnclosingMethodInfo : public AttributeInfo {
public:
    AttributeEnclosingMethodInfo()
	: AttributeInfo("EnclosingMethod")
    {
    }
    void ReadInfo(ClassReader& reader) override;

private:
    u2 class_index_;
    u2 method_index_;
};

template <bool synthetic = true>
class AttributeSyntheticInfo : public AttributeInfo {
public:
    AttributeSyntheticInfo()
	: AttributeInfo(synthetic ? "Synthetic" : "Deprecated")
    {
    }
    void ReadInfo(ClassReader&) override {}
};

using AttributeDeprecatedInfo = AttributeSyntheticInfo<false>;

class AttributeSignatureInfo : public AttributeInfo {
public:
    AttributeSignatureInfo()
	: AttributeInfo("Signature")
    {
    }
    void ReadInfo(ClassReader&) override;

private:
    u2 signature_index_;
};
class AttributeSourceFileInfo : public AttributeInfo {
public:
    AttributeSourceFileInfo()
	: AttributeInfo("SourceFile")
    {
    }
    void ReadInfo(ClassReader&) override;

private:
    u2 sourcefile_index_;
};

struct LineNumberInfo {
    u2 start_pc;
    u2 line_number;
};
class AttributeLineNumberTableInfo : public AttributeInfo {
public:
    AttributeLineNumberTableInfo()
	: AttributeInfo("LineNumberTable")
    {
    }
    void ReadInfo(ClassReader&) override;

private:
    std::vector<LineNumberInfo> line_number_table_;
};

struct LocalVariableInfo {
    u2 start_pc;
    u2 length;
    u2 name_index;
    u2 descriptor_index;
    u2 index;
};

struct LocalVariableTypeInfo {
    u2 start_pc;
    u2 length;
    u2 name_index;
    u2 signature_index;
    u2 index;
};

class AttributeLocalVariableTableInfo : public AttributeInfo {
public:
    AttributeLocalVariableTableInfo()
	: AttributeInfo("LocalVariableTable")
    {
    }
    void ReadInfo(ClassReader&) override;

private:
    std::vector<LocalVariableInfo> local_variable_table_;
};

class AttributeLocalVariableTypeTableInfo : public AttributeInfo {
public:
    AttributeLocalVariableTypeTableInfo()
	: AttributeInfo("LocalVariableTypeTable")
    {
    }
    void ReadInfo(ClassReader&) override;

private:
    std::vector<LocalVariableTypeInfo> local_variable_type_table_;
};
class AttributeUnparsedInfo : public AttributeInfo {
public:
    AttributeUnparsedInfo(std::string attr_name, u4 attr_len)
	: AttributeInfo("Unparsed")
	, attr_name_(attr_name)
	, attr_len_(attr_len)
    {
    }
    void ReadInfo(ClassReader&) override;

private:
    bytes data_;
    std::string attr_name_;
    u4 attr_len_;
};

struct BootStrapMethod {
    u2 bootstrap_method_ref;
    std::vector<u2> bootstrap_arguments;
};

class AttributeBootstrapMethodsInfo : public AttributeInfo {
public:
    AttributeBootstrapMethodsInfo()
	: AttributeInfo("BootstrapMethods")
    {
    }

    void ReadInfo(ClassReader&) override;

private:
    std::vector<BootStrapMethod> bootStrap_methods_;
};
}
#endif
