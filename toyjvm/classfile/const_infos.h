//
// Created by cyhone on 18-2-8.
//

#ifndef TOYJVM_CONST_INFOS_H
#define TOYJVM_CONST_INFOS_H

#include <toyjvm/utilities/basereader.h>
#include <toyjvm/utilities/jvm_types.h>
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

        virtual void read(BaseReader &)
        {}

        ConstType constTag() const
        {
            return tag_;
        }

    protected:
        ConstType tag_;
        const ConstPool &const_pool_;
    };


    class ConstClassInfo : public BaseConstInfo {
    public:
        explicit ConstClassInfo(ConstPool &const_pool)
                : BaseConstInfo(ConstType::Class, const_pool)
        {}

        void read(BaseReader &) override;

        const std::string &className();

    private:
        u2 name_index_;
        std::string class_name_;
    };

    class ConstNameAndTypeInfo : public BaseConstInfo {
    public:
        explicit ConstNameAndTypeInfo(ConstPool &const_pool)
                : BaseConstInfo(ConstType::NameAndType, const_pool)
        {}

        std::array<std::string, 2> nameAndDescriptor() const;

        void read(BaseReader &) override;

    private:
        u2 name_index_;
        u2 descriptor_index_;
    };

    template<ConstType tag>
    class BaseMemberRefInfo : public BaseConstInfo {
    public:
        explicit BaseMemberRefInfo(ConstPool &const_pool)
                : BaseConstInfo(tag, const_pool)
        {}

        void read(jvm::BaseReader &reader){
            class_index_ = reader.read<u2>();
            name_and_type_index_ = reader.read<u2>();
        }

        std::array<std::string, 2> nameAndDescriptor() const{
            return const_pool_.constInfoAt<ConstNameAndTypeInfo>(name_and_type_index_)
                    ->nameAndDescriptor();
        };

        std::string className() const{
            return const_pool_.classNameOf(class_index_);
        }

    private:
        u2 class_index_;
        u2 name_and_type_index_;
    };

    using ConstFieldRefInfo = BaseMemberRefInfo<ConstType::FieldRef>;
    using ConstMethodRefInfo = BaseMemberRefInfo<ConstType::MethodRef>;
    using ConstInterfaceMethodRefInfo = BaseMemberRefInfo<ConstType::InterfaceMethodRef>;

    class ConstStringInfo : public BaseConstInfo {
    public:
        explicit ConstStringInfo(ConstPool &const_pool)
                : BaseConstInfo(ConstType::String, const_pool)
        {}

        void read(BaseReader &) override;

        std::string val() const;

    private:
        u2 string_index_;
    };



    template<ConstType tag, typename T>
    class BaseNumberInfo : public BaseConstInfo{
    public:
        explicit BaseNumberInfo(ConstPool &const_pool)
                : BaseConstInfo(tag, const_pool)
        {}

        void read(BaseReader &reader) override
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

    using ConstFloatInfo = BaseNumberInfo<ConstType::Float, jfloat>;
    using ConstDoubleInfo = BaseNumberInfo<ConstType::Double, jdouble>;
    using ConstIntegerInfo = BaseNumberInfo<ConstType::Integer, jint>;
    using ConstLongInfo = BaseNumberInfo<ConstType::Long, jlong>;


    class ConstUtf8Info : public BaseConstInfo {
    public:
        explicit ConstUtf8Info(ConstPool &const_pool)
                : BaseConstInfo(ConstType::Utf8, const_pool)
        {}

        void read(BaseReader &) override;

        std::string asString();

    private:
        bytes data_;
    };

    class ConstMethodHandleInfo : public BaseConstInfo {
    public:
        explicit ConstMethodHandleInfo(ConstPool &const_pool)
                : BaseConstInfo(ConstType::MethodHandle, const_pool)
        {}

        void read(BaseReader &) override;

    private:
        u1 reference_kind_;
        u2 reference_index_;
    };

    class ConstMethodTypeInfo : public BaseConstInfo {
    public:
        explicit ConstMethodTypeInfo(ConstPool &const_pool)
                : BaseConstInfo(ConstType::MethodType, const_pool)
        {}

        void read(BaseReader &) override;

    private:
        u2 descriptor_index_;
    };

    class ConstInvokeDynamicInfo : public BaseConstInfo {
    public:
        explicit ConstInvokeDynamicInfo(ConstPool &const_pool)
                : BaseConstInfo(ConstType::InvokeDynamic, const_pool)
        {}

        void read(BaseReader &) override;

    private:
        u2 boostrap_method_attr_index_;
        u2 name_and_type_index_;
    };
}
#endif //TOYJVM_CONST_INFO_H
