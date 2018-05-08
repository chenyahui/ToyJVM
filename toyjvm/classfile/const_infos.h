//
// Created by cyhone on 18-2-8.
//

#ifndef TOYJVM_CONST_INFOS_H
#define TOYJVM_CONST_INFOS_H

#include <toyjvm/utilities/bytereader.h>
#include <toyjvm/utilities/jvm_types.h>
#include <toyjvm/utilities/modified_utf8.h>
#include <toyjvm/classfile/const_pool.h>
#include <boost/noncopyable.hpp>
#include <string>

namespace jvm {
    class BaseConstInfo : boost::noncopyable {
    public:
        BaseConstInfo(ConstType const_tag, const ConstPool &const_pool)
                : tag_(const_tag), const_pool_(const_pool)
        {}

        virtual ~BaseConstInfo() = default;

        virtual void read(ByteReader &)
        {}

        ConstType tag() const
        {
            return tag_;
        }

    protected:
        ConstType tag_;
        const ConstPool &const_pool_;
    };


    class ConstClassInfo : public BaseConstInfo {
    public:
        ConstClassInfo(ConstType const_tag, ConstPool &const_pool)
                : BaseConstInfo(const_tag, const_pool)
        {}

        void read(ByteReader &) override;

        const std::string &className();

    private:
        u2 name_index_;
        std::string class_name_;
    };

    class ConstNameAndTypeInfo : public BaseConstInfo {
    public:
        ConstNameAndTypeInfo(ConstType const_tag, ConstPool &const_pool)
                : BaseConstInfo(const_tag, const_pool)
        {}

        std::array<std::string, 2> nameAndDescriptor() const;

        void read(ByteReader &) override;

    private:
        u2 name_index_;
        u2 descriptor_index_;
    };

    class BaseMemberRefInfo : public BaseConstInfo {
    public:
        BaseMemberRefInfo(ConstType const_tag, ConstPool &const_pool)
                : BaseConstInfo(const_tag, const_pool)
        {}

        void read(jvm::ByteReader &reader) override;

        std::array<std::string, 2> nameAndDescriptor() const;

        std::string className() const;

    private:
        u2 class_index_;
        u2 name_and_type_index_;
    };

    using ConstFieldRefInfo = BaseMemberRefInfo;
    using ConstMethodRefInfo = BaseMemberRefInfo;
    using ConstInterfaceMethodRefInfo = BaseMemberRefInfo;

    class ConstStringInfo : public BaseConstInfo {
    public:
        ConstStringInfo(ConstType const_tag, ConstPool &const_pool)
                : BaseConstInfo(const_tag, const_pool)
        {}

        void read(ByteReader &) override;

        ModifiedUTF8& val() const;


    private:
        u2 string_index_;
    };


    template<typename T>
    class BaseNumberInfo : public BaseConstInfo {
    public:
        BaseNumberInfo(ConstType const_tag, ConstPool &const_pool)
                : BaseConstInfo(const_tag, const_pool)
        {}

        void read(ByteReader &reader) override
        {
            val_ = reader.read<T>();
        }

        T val() const
        {
            return val_;
        }

    private:
        T val_;
    };

    using ConstFloatInfo = BaseNumberInfo<jfloat>;
    using ConstDoubleInfo = BaseNumberInfo<jdouble>;
    using ConstIntegerInfo = BaseNumberInfo<jint>;
    using ConstLongInfo = BaseNumberInfo<jlong>;


    class ConstUtf8Info : public BaseConstInfo {
    public:
        ConstUtf8Info(ConstType const_tag, ConstPool &const_pool)
                : BaseConstInfo(const_tag, const_pool)
        {}

        void read(ByteReader &) override;

        std::string asString();

        ModifiedUTF8 &val();

    private:
        ModifiedUTF8 utf8_;
    };

    class ConstMethodHandleInfo : public BaseConstInfo {
    public:
        ConstMethodHandleInfo(ConstType const_tag, ConstPool &const_pool)
                : BaseConstInfo(const_tag, const_pool)
        {}

        void read(ByteReader &) override;

    private:
        u1 reference_kind_;
        u2 reference_index_;
    };

    class ConstMethodTypeInfo : public BaseConstInfo {
    public:
        ConstMethodTypeInfo(ConstType const_tag, ConstPool &const_pool)
                : BaseConstInfo(const_tag, const_pool)
        {}

        void read(ByteReader &) override;

    private:
        u2 descriptor_index_;
    };

    class ConstInvokeDynamicInfo : public BaseConstInfo {
    public:
        ConstInvokeDynamicInfo(ConstType const_tag, ConstPool &const_pool)
                : BaseConstInfo(const_tag, const_pool)
        {}

        void read(ByteReader &) override;

    private:
        u2 boostrap_method_attr_index_;
        u2 name_and_type_index_;
    };
}
#endif //TOYJVM_CONST_INFO_H
