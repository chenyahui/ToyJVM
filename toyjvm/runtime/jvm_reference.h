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
    class JvmRef : boost::noncopyable {
    public:
        explicit JvmRef(JvmBaseClass *klass)
                : klass_(klass)
        {}

        JvmBaseClass *klass() const
        {
            return klass_;
        }

        bool isInstanceOf(JvmBaseClass *t) const
        {
            return klass_->isAssignableFrom(t);
        }

        virtual ~JvmRef() = default;

        bool hasExtra() const;

        void setExtra(boost::any data)
        {
            extra_ = data;
        }

        template<typename T>
        T getExtra()
        {
            return boost::any_cast<T>(extra_);
        }

    protected:
        JvmBaseClass *klass_;
        boost::any extra_;
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

        void setRef(const std::string &name, const std::string &descriptor, jref ref_obj);

        jref getRef(const std::string &name, const std::string &descriptor);

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
        JvmArray(u4 count,
                 JvmArrayClass *array_class)
                : JvmBaseArray(array_class)
        {}

        JvmArray(std::vector<T> data, JvmArrayClass *array_class)
                : JvmBaseArray(array_class),
                  data_(std::move(data))
        {}

        int arrayLen() const override
        {
            return data_.size();
        }

        T at(int index)
        {
            return data_[index];
        }

        void set(int index, T val)
        {
            data_[index] = val;
        }

        std::vector<T> &rawData()
        {
            return data_;
        }


    private:
        std::vector<T> data_;
    };
}

#endif //TOYJVM_JVM_REFERENCE_H
