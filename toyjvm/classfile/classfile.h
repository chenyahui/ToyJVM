//
// Created by cyhone on 18-1-30.
//

#ifndef TOYJVM_CLASSFILE_H
#define TOYJVM_CLASSFILE_H

#include <toyjvm/classfile/const_pool.h>
#include <toyjvm/classfile/member_info.h>
#include <toyjvm/classfile/attribute_table.h>
#include <toyjvm/utilities/jvm_types.h>
#include <utility>
#include <boost/noncopyable.hpp>
#include <vector>
#include <memory>

namespace jvm {
    class JvmClass;

    class ClassFile : boost::noncopyable {
    public:
        friend class JvmClass;

        explicit ClassFile(bytes data)
                : reader_(data)
        {}

        ~ClassFile();

        void parse();

        inline std::string className()
        {
            return const_pool_.classNameOf(this_class_);
        }

        void logClassInfo();

        AttrSourceFile *sourceFileAttr() const;

    private:
        void checkMagicAndVersions();

        template<typename T>
        std::vector<T *> readMembers()
        {
            auto count = reader_.read<u2>();
            std::vector<T *> members;
            members.reserve(count);

            for (int i = 0; i < count; ++i) {
                auto member = new T(const_pool_);
                member->read(reader_);
                members.push_back(member);
            }
            return members;
        };


    private:
        ByteReader reader_;

        ConstPool const_pool_;
        u2 access_flags_;
        u2 this_class_;
        u2 super_class_;

        std::vector<FieldInfo *> fields_;
        std::vector<MethodInfo *> methods_;

        std::vector<u2> interfaces_;
        AttrTable attr_table_;
    };
}


#endif //NEWJVM_CLASSFILE_H
