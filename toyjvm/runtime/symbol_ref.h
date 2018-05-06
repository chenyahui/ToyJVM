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
        explicit SymbolRef(RuntimeConstPool &runtime_const_pool, const std::string &)
                : runtime_const_pool_(runtime_const_pool),
                  klass_(nullptr)
        {}

        JvmClass *resolveClass();

    protected:
        RuntimeConstPool &runtime_const_pool_;
        std::string class_name_;
        JvmClass *klass_; // 表示该符号代表的类

    };

    class ClassRef : public SymbolRef {
    public:
        ClassRef(RuntimeConstPool &runtime_const_pool,
                 ConstClassInfo *class_info)
                : SymbolRef(runtime_const_pool, class_info->className())
        {
        }
    };

    class MemberRef : public SymbolRef {
    public:
        MemberRef(RuntimeConstPool &runtime_const_pool,
                  BaseMemberRefInfo *member_info)
                : SymbolRef(runtime_const_pool, member_info->className()),
                  name_descriptor_(member_info->nameAndDescriptor())
        {
        }

        const std::string &name() const
        {
            return name_descriptor_[0];
        }

        const std::string &descriptor() const
        {
            return name_descriptor_[1];
        }

    protected:
        std::array<std::string, 2> name_descriptor_;
    };

    class FieldRef : public MemberRef {
    public:
        FieldRef(RuntimeConstPool &runtime_const_pool,
                 ConstFieldRefInfo *field_info)
                : MemberRef(runtime_const_pool, field_info),
                  field_(nullptr)
        {

        }

        JvmField *resolveField();

    protected:
        JvmField *lookUpField(JvmClass *klass);

    protected:
        JvmField *field_;
    };


    JvmMethod *lookUpMethodInClass(JvmClass *klass,
                                   const std::string &name,
                                   const std::string &descriptor);

    JvmMethod *lookUpMethodInInterfaces(const std::vector<JvmClass *> &ifaces,
                                        const std::string &name,
                                        const std::string &descriptor);

    class MethodRef : public MemberRef {
    public:
        MethodRef(RuntimeConstPool &runtime_const_pool,
                  ConstMethodRefInfo *method_info)
                : MemberRef(runtime_const_pool, method_info),
                  method_(nullptr)
        {}

        JvmMethod *resolveMethod();

    private:
        JvmMethod *method_;
    };

    class InterfaceMethodRef : public MemberRef {
    public:
        InterfaceMethodRef(RuntimeConstPool &runtime_const_pool,
                           ConstInterfaceMethodRefInfo *method_info)
                : MemberRef(runtime_const_pool, method_info),
                  method_(nullptr)
        {}

        JvmMethod *resolveInterfaceMethod();

    protected:
        JvmMethod *method_;
    };
}
#endif //TOYJVM_SYMBOL_REF_H
