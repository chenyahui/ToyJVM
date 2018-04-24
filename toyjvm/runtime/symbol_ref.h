//
// Created by cyhone on 18-4-21.
//

#ifndef TOYJVM_SYMBOL_REF_H
#define TOYJVM_SYMBOL_REF_H

#include <boost/noncopyable.hpp>
#include <toyjvm/runtime/runtime_const_pool.h>
#include <toyjvm/runtime/jvm_class.h>
#include <toyjvm/classfile/const_infos.h>

namespace jvm {
    class SymbolRef : boost::noncopyable {
    public:
        explicit SymbolRef(RuntimeConstPool &runtime_const_pool)
                : runtime_const_pool_(runtime_const_pool),
                  klass_(nullptr)
        {}

        std::shared_ptr<JvmClass> resolveClass();

    protected:
        RuntimeConstPool &runtime_const_pool_;
        std::string class_name_;
        std::shared_ptr<JvmClass> klass_; // 表示该符号代表的类

    };

    class ClassRef : public SymbolRef {
    public:
        ClassRef(RuntimeConstPool &runtime_const_pool,
                 ConstClassInfo *class_info)
                : SymbolRef(runtime_const_pool),
                  class_name_(class_info->className())
        {
        }
    };

    template<ConstType tag>
    class MemberRef : public SymbolRef {
    public:
        MemberRef(RuntimeConstPool &runtime_const_pool,
                  BaseMemberRefInfo<tag> *member_info)
                : SymbolRef(runtime_const_pool),
                  class_name_(member_info->className()),
                  name_descriptor_(member_info->nameAndDescriptor())
        {
        }

    protected:
        std::array<std::string, 2> name_descriptor_;
    };

    class FieldRef : public MemberRef<ConstType::FieldRef> {
    public:
        FieldRef(RuntimeConstPool &runtime_const_pool,
                 ConstFieldRefInfo *field_info)
                : MemberRef(runtime_const_pool, field_info),
                  field_(nullptr)
        {

        }

        std::shared_ptr<JvmField> resolveField();

    protected:
        std::shared_ptr<JvmField> lookUpField(JvmClass *klass);

    protected:
        std::shared_ptr<JvmField> field_;
    };

    class MethodRef : public MemberRef<ConstType::MethodRef> {
    public:
        MethodRef(RuntimeConstPool &runtime_const_pool,
                  ConstMethodRefInfo *method_info)
                : MemberRef(runtime_const_pool, method_info),
                  method_(nullptr)
        {

        }

    protected:
        std::shared_ptr<JvmMethod> method_;
    };

    class InterfaceMethodRef : public MemberRef<ConstType::InterfaceMethodRef> {
    public:
        InterfaceMethodRef(RuntimeConstPool &runtime_const_pool,
                           ConstInterfaceMethodRefInfo *method_info)
                : MemberRef(runtime_const_pool, method_info),
                  method_(nullptr)
        {

        }

    protected:
        std::shared_ptr<JvmMethod> method_;
    };
}
#endif //TOYJVM_SYMBOL_REF_H
