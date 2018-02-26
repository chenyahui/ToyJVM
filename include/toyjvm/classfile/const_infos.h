//
// Created by cyhone on 18-2-8.
//

#ifndef TOYJVM_CONST_INFOS_H
#define TOYJVM_CONST_INFOS_H

#include <toyjvm/common/basereader.h>
#include "toyjvm/common/uncopyable.h"
#include "toyjvm/common/jvm_types.h"
#include "toyjvm/classfile/const_pool.h"

namespace jvm {
    class BaseConstInfo : UnCopyable {
    public:
        BaseConstInfo(ConstPool::ConstType tag, ConstPool *const_pool)
                : tag_(tag), const_pool_(const_pool)
        {}

        virtual ~ConstantInfo()
        {}

        virtual void Read(BaseReader &)
        {}

    protected:
        ConstPool::ConstType tag_;
        ConstPool *const_pool_;
    };


    class ConstClassInfo : public BaseConstInfo {
    public:
        ConstClassInfo(ConstPool *const_pool)
                : BaseConstInfo(ConstPool::ConstType::Class, const_pool)
        {}

        void Read(BaseReader &) override;

    private:
        u2 name_index_;
    };

    template<ConstPool::ConstType tag>
    class BaseMemberRefInfo : public BaseConstInfo {
    public:
        BaseMemberRefInfo(ConstPool *const_pool)
                : BaseConstInfo(tag, const_pool)
        {}

        void Read(BaseReader &) override;

    private:
        u2 class_index_;
        u2 name_and_type_index_;
    };

    using ConstFieldRefInfo = BaseMemberRefInfo<ConstPool::ConstType::FieldRef>;
    using ConstMethodRefInfo = BaseMemberRefInfo<ConstPool::ConstType::MethodRef>;
    using ConstInterfaceMethodRefInfo = BaseMemberRefInfo<ConstPool::ConstType::InterfaceMethodRef>;

    class ConstStringInfo : public BaseConstInfo {
    public:
        ConstStringInfo(ConstPool *const_pool)
                : BaseConstInfo(ConstPool::ConstType::String, const_pool)
        {}

        void Read(BaseReader &) override;

    private:
        u2 string_index_;
    };

    template<ConstPool::ConstType tag, typename T>
    class BaseNumberInfo : public BaseConstInfo {
    public:
        BaseNumberInfo(ConstPool *const_pool)
                : BaseConstInfo(tag, const_pool)
        {}

        void Read(BaseReader &reader) override
        {
            val_ = reader.Read<T>();
        }

        T val() const
        {
            return val_;
        }

    private:
        T val_;
    };

    using ConstFloatInfo = BaseNumberInfo<ConstPool::ConstType::Float, float>;
    using ConstDoubleInfo = BaseNumberInfo<ConstPool::ConstType::Double, double>;
    using ConstIntegerInfo = BaseNumberInfo<ConstPool::ConstType::Integer, int>;
    using ConstLongInfo = BaseNumberInfo<ConstPool::ConstType::Long, long>;

    class ConstNameAndTypeInfo : public BaseConstInfo {
    public:
        ConstNameAndTypeInfo(ConstPool *const_pool)
                : BaseConstInfo(ConstPool::ConstType::NameAndType, const_pool)
        {}

        void Read(BaseReader &) override;

    private:
        u2 name_index_;
        u2 descriptor_index_;
    };

    class ConstUtf8Info : public BaseConstInfo {
    public:
        ConstUtf8Info(ConstPool *const_pool)
                : BaseConstInfo(ConstPool::ConstType::Utf8, const_pool)
        {}

        void Read(BaseReader &) override;

    private:
        bytes data_;
    };

    class ConstMethodHandleInfo : public BaseConstInfo {
    public:
        ConstMethodHandleInfo(ConstPool *const_pool)
                : BaseConstInfo(ConstPool::ConstType::MethodHandle, const_pool)
        {}

        void Read(BaseReader &) override;

    private:
        u1 reference_kind_;
        u2 reference_index_;
    };

    class ConstMethodTypeInfo : public BaseConstInfo {
    public:
        ConstMethodTypeInfo(ConstPool *const_pool)
                : BaseConstInfo(ConstPool::ConstType::MethodType, const_pool)
        {}

        void Read(BaseReader &) override;

    private:
        u2 descriptor_index_;
    };

    class ConstInvokeDynamicInfo : public BaseConstInfo {
    public:
        ConstInvokeDynamicInfo(ConstPool *const_pool)
                : BaseConstInfo(ConstPool::ConstType::InvokeDynamic, const_pool)
        {}

        void Read(BaseReader &) override;

    private:
        u2 boostrap_method_attr_index_;
        u2 name_and_type_index_;
    };
}
#endif //TOYJVM_CONST_INFO_H
