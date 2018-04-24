//
// Created by cyhone on 18-2-8.
//

#ifndef TOYJVM_ATTRIBUTE_INFOS_H
#define TOYJVM_ATTRIBUTE_INFOS_H

#include <string>
#include <boost/noncopyable.hpp>
#include <toyjvm/utilities/basereader.h>
#include <toyjvm/classfile/const_pool.h>
#include <memory>

namespace jvm {
    class AttrTable;

    class BaseAttrInfo {
    public:
        BaseAttrInfo(const std::string &attr_type, const ConstPool &const_pool)
                : attr_type_(attr_type), const_pool_(const_pool)
        {}

        virtual void read(BaseReader &reader)
        {}

        inline const std::string &attrType() const
        {
            return attr_type_;
        }

        virtual ~BaseAttrInfo() = default;

    protected:
        const std::string attr_type_;
        const ConstPool &const_pool_;
    };

    class AttrConstantValue : public BaseAttrInfo {
    public:
        explicit AttrConstantValue(const ConstPool &const_pool)
                : BaseAttrInfo("ConstantValue", const_pool)
        {
        }

        void read(BaseReader &reader) override;

        inline u2 constValueIndex() const
        {
            return constant_value_index_;
        }

    private:
        u2 constant_value_index_;
    };

    struct ExceptionInfo {
        u2 start_pc;
        u2 end_pc;
        u2 handler_pc;
        u2 catch_type;
    };

    /*
     * TODO 对于bytes data类型的数据，没有必要再存储一份吧，直接建立映射
     */
    class AttrCode : public BaseAttrInfo {
    public:
        explicit AttrCode(const ConstPool &const_pool);

        void read(BaseReader &reader) override;

    public:
        inline u2 maxStack() const
        {
            return max_stack_;
        }

        inline u2 maxLocals() const
        {
            return max_locals_;
        }

        inline bytes moveCode()
        {
            return std::move(code_);
        }

    private:
        u2 max_stack_;
        u2 max_locals_;
        bytes code_;
        std::vector<ExceptionInfo> exception_table_;
        std::unique_ptr<AttrTable> attr_table_;
    };

    class AttrExceptions : public BaseAttrInfo {
    public:
        explicit AttrExceptions(const ConstPool &const_pool)
                : BaseAttrInfo("Exceptions", const_pool)
        {}

        void read(BaseReader &reader) override;

    private:
        std::vector<u2> exception_index_table_;
    };

    struct InnerClassInfo {
        u2 inner_class_info_index;
        u2 outer_class_info_index;
        u2 inner_name_index;
        u2 inner_class_access_flags;
    };

    class AttrInnerClasses : public BaseAttrInfo {
    public:
        explicit AttrInnerClasses(const ConstPool &const_pool)
                : BaseAttrInfo("InnerClasses", const_pool)
        {}

        void read(BaseReader &reader) override;

    private:
        std::vector<InnerClassInfo> inner_classes_;
    };

    class AttrEnclosingMethod : public BaseAttrInfo {
    public:
        explicit AttrEnclosingMethod(const ConstPool &const_pool)
                : BaseAttrInfo("EnclosingMethod", const_pool)
        {}

        void read(BaseReader &reader) override;

    private:
        u2 class_index_;
        u2 method_index_;
    };

    template<char const *attr_type>
    class EmptyAttrInfo : public BaseAttrInfo {
    public:
        explicit EmptyAttrInfo(const ConstPool &const_pool)
                : BaseAttrInfo(attr_type, const_pool)
        {}
    };

    // 所以！！！ char* 和 char[]的区别
    static constexpr const char Synthetic[] = "Synthetic";
    static constexpr const char Deprecated[] = "Deprecated";

    using AttrSynthetic = EmptyAttrInfo<Synthetic>;
    using AttrDeprecated = EmptyAttrInfo<Deprecated>;

    class AttrSignature : public BaseAttrInfo {
    public:
        explicit AttrSignature(const ConstPool &const_pool)
                : BaseAttrInfo("Signature", const_pool)
        {}

        void read(BaseReader &reader) override;

    private:
        u2 signature_index_;
    };

    class AttrSourceFile : public BaseAttrInfo {
    public:
        explicit AttrSourceFile(const ConstPool &const_pool)
                : BaseAttrInfo("SourceFile", const_pool)
        {}

        void read(BaseReader &reader) override;

    private:
        u2 sourcefile_index_;;
    };

    struct LineNumberInfo {
        u2 start_pc;
        u2 line_number;
    };

    class AttrLineNumberTable : public BaseAttrInfo {
    public:
        explicit AttrLineNumberTable(const ConstPool &const_pool)
                : BaseAttrInfo("LineNumberTable", const_pool)
        {}

        void read(BaseReader &reader) override;

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

    class AttrLocalVariableTable : public BaseAttrInfo {
    public:
        explicit AttrLocalVariableTable(const ConstPool &const_pool)
                : BaseAttrInfo("LocalVariableTable", const_pool)
        {}

        void read(BaseReader &reader) override;

    private:
        std::vector<LocalVariableInfo> local_variable_table_;
    };

    struct LocalVariableTypeInfo {
        u2 start_pc;
        u2 length;
        u2 name_index;
        u2 signature_index;
        u2 index;
    };

    class AttrLocalVariableTypeTable : public BaseAttrInfo {
    public:
        explicit AttrLocalVariableTypeTable(const ConstPool &const_pool)
                : BaseAttrInfo("LocalVariableTypeTable", const_pool)
        {}

        void read(BaseReader &reader) override;

    private:
        std::vector<LocalVariableTypeInfo> local_variable_type_table_;
    };

    struct BootStrapMethod {
        u2 bootstrap_method_ref;
        std::vector<u2> bootstrap_arguments;
    };

    class AttrBootstrapMethods : public BaseAttrInfo {
    public:
        explicit AttrBootstrapMethods(const ConstPool &const_pool)
                : BaseAttrInfo("BootstrapMethods", const_pool)
        {}

        void read(BaseReader &reader) override;

    private:
        std::vector<BootStrapMethod> bootStrap_methods_;
    };

    class AttrUnparsed : public BaseAttrInfo {
    public:
        explicit AttrUnparsed(std::string &attr_name, u4 attr_len, const ConstPool &const_pool)
                : BaseAttrInfo(attr_name, const_pool),
                  attr_len_(attr_len)
        {}

        void read(BaseReader &reader) override;

    private:
        u4 attr_len_;
        bytes data_;
    };
}
#endif //TOYJVM_ATTRIBUTE_INFOS_H
