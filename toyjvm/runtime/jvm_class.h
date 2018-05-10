//
// Created by cyhone on 2018/3/9.
//

#ifndef TOYJVM_JVM_CLASS_H
#define TOYJVM_JVM_CLASS_H

#include <boost/noncopyable.hpp>
#include <toyjvm/classfile/classfile.h>
#include <toyjvm/utilities/access_flags.h>
#include <toyjvm/runtime/runtime_const_pool.h>
#include <toyjvm/runtime/local_slots.h>
#include <toyjvm/utilities/jvm_types.h>

namespace jvm {

    class JvmField;

    class JvmMethod;

    class ClassLoader;

    class JvmBaseClass : boost::noncopyable {
    public:
        friend class ClassLoader;

        JvmBaseClass(const std::string &class_name, jint flags)
                : access_flags_(flags),
                  class_name_(class_name)
        {}

        const std::string &name() const;

        std::string javaName() const;

        const std::string &descriptor() const;

        const std::vector<JvmClass *> &interfaces() const;

        JvmClass *superClass() const;

        const AccessFlags &accessFlags() const;

        virtual bool isAssignableFrom(JvmBaseClass *t) const;

        bool isSubClassOf(JvmBaseClass *klass) const;

        bool isImplements(JvmBaseClass *klass) const;

        bool isArray() const
        {
            return is_array_;
        }

        bool isPrimitive() const
        {
            return is_primitive_;
        }

        JvmRef *metaClass() const
        {
            return meta_class_;
        }

    protected:
        bool is_array_ = false;
        bool is_primitive_ = false;
        std::string class_name_;
        AccessFlags access_flags_;
        JvmClass *super_class_ = nullptr;
        std::vector<JvmClass *> interfaces_;
        mutable std::string class_descriptor_;

        JvmRef *meta_class_;
    };

    class JvmPrimitiveClass : public JvmBaseClass {
    public:
        explicit JvmPrimitiveClass(const std::string &class_name);
    };

    class JvmArrayClass : public JvmBaseClass {
    public:
        explicit JvmArrayClass(const std::string &class_name);

        bool isAssignableFrom(JvmBaseClass *t) const override;

        JvmBaseArray *arrayFactory(u4 count);

        JvmBaseClass *componentClass() const;

    private:
        std::string component_name_;
    };

    class JvmClass : public JvmBaseClass {
    public:
        explicit JvmClass(ClassFile *class_file);

        JvmField *getField(const std::string &name, const std::string &descriptor, bool isStatic);

        JvmMethod *getMainMethod();

        JvmMethod *getStaticMethod(const std::string &name, const std::string &descriptor);

        bool isSubInterfaceOf(JvmClass *) const;

        size_t instanceSlotsCount() const
        {
            return instance_slots_count_;
        }

        void setInstanceSlotsCount(size_t val)
        {
            instance_slots_count_ = val;
        }

        void allocStaticSlots(size_t val)
        {
            static_slots_count_ = val;
            static_fields_ = std::move(std::unique_ptr<LocalSlots>(new LocalSlots(static_slots_count_)));
        }

        LocalSlots *staticFields() const
        {
            return static_fields_.get();
        }

        const RuntimeConstPool &runtimeConstPool() const
        {
            return runtime_const_pool_;
        }

        const std::vector<JvmField *> &fields() const
        {
            return fields_;
        }

        const std::vector<JvmMethod *> &methods() const
        {
            return methods_;
        }
        std::string& sourceFileName() const;

    private:
        bool isJavaLangObject();

    private:
        RuntimeConstPool runtime_const_pool_;

        std::string source_file_name_;
        std::vector<JvmField *> fields_;
        std::vector<JvmMethod *> methods_;
        size_t instance_slots_count_;
        size_t static_slots_count_;
        std::unique_ptr<LocalSlots> static_fields_;
    };
}
#endif //TOYJVM_JVM_CLASS_H
