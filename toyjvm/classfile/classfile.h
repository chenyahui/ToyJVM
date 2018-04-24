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
                : reader_(std::move(data)),
                  const_pool_(reader_)
        {}

        void parse();

        void logClassInfo();

        inline std::string className()
        {
            return const_pool_.classNameOf(this_class_);
        }

    private:
        void checkMagicAndVersions();

        template<typename T,
                typename std::enable_if<std::is_base_of<MemberInfo, T>::value>::type>
        std::vector<std::shared_ptr<T>> readMembers()
        {
            auto count = reader_.read<u2>();
            std::vector<std::shared_ptr<T>> result;
            result.reserve(count);

            for (int i = 0; i < count; ++i) {
                auto member = std::make_shared<T>(const_pool_);
                member->read(reader_);
                result.push_back(member);
            }
            return result;
        };


    private:
        BaseReader reader_;

        ConstPool const_pool_;
        u2 access_flags_;
        u2 this_class_;
        u2 super_class_;
        std::vector<std::shared_ptr<FieldInfo>> fields_;
        std::vector<std::shared_ptr<MethodInfo>> methods_;
        std::vector<u2> interfaces_;
        AttrTable attr_table_;
    };
}


#endif //NEWJVM_CLASSFILE_H
