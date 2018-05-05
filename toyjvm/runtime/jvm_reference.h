//
// Created by cyhone on 18-4-22.
//

#ifndef TOYJVM_JVM_REFERENCE_H
#define TOYJVM_JVM_REFERENCE_H

#include <boost/noncopyable.hpp>
#include <memory>
#include <toyjvm/runtime/jvm_class.h>
#include <toyjvm/runtime/local_slots.h>

namespace jvm {
    class JvmRef : boost::noncopyable{
    public:
        explicit JvmRef(JvmBaseClass *klass)
                : klass_(klass)
        {}

        JvmBaseClass* klass() const
        {
            return klass_;
        }

        bool isInstanceOf(JvmBaseClass *t) const
        {
            return klass_->isAssignableFrom(t);
        }

        virtual ~JvmRef() = default;

    protected:
        JvmBaseClass *klass_;
    };

    class JvmObject : public JvmRef {
    public:
        explicit JvmObject(JvmClass *klass)
                : JvmRef(klass),
                  instance_fields_(klass->instanceSlotsCount())
        {}

        const jvm::LocalSlots &instanceFields() const
        {
            return instance_fields_;
        }

        virtual ~JvmObject() = default;

    private:
        jvm::LocalSlots instance_fields_;
    };


    class JvmBaseArray : public JvmRef {
    public:
        explicit JvmBaseArray(JvmArrayClass *array_class)
                : JvmRef(array_class)
        {}

        virtual int arrayLen() const = 0;

        virtual ~JvmBaseArray() = default;
    };

    template<typename T>
    class JvmArray : public JvmBaseArray {
    public:
        explicit JvmArray(u4 count,
                          JvmArrayClass *array_class)
                : JvmBaseArray(array_class)
        {}

        int arrayLen() const override
        {
            return data_.size();
        }

    private:
        std::vector<T> data_;
    };
}

#endif //TOYJVM_JVM_REFERENCE_H
