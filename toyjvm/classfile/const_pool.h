//
// Created by cyhone on 18-2-8.
//

#ifndef TOYJVM_CONST_POOL_H
#define TOYJVM_CONST_POOL_H

#include <toyjvm/common/basereader.h>
#include <string>

namespace jvm {
    class BaseConstInfo;

    class ConstPool : boost::noncopyable {
    public:
        enum ConstType {
            Class = 7,
            FieldRef = 9,
            MethodRef = 10,
            InterfaceMethodRef = 11,
            String = 8,
            Integer = 3,
            Float = 4,
            Long = 5,
            Double = 6,
            NameAndType = 12,
            Utf8 = 1,
            MethodHandle = 15,
            MethodType = 16,
            InvokeDynamic = 18
        };

        explicit ConstPool(BaseReader &reader)
                : reader_(reader)
        {}


        void read();

        BaseConstInfo *ConstInfoFactory(ConstType tag);

        ~ConstPool();

    public:
        std::string stringAt(int index) const;

        template<typename T>
        T *constInfoAt(int index) const
        {
            assert(index >= 1 && index < const_infos_.size());
            auto info = dynamic_cast<T *>(const_infos_[index]);
            assert(info != nullptr);
            return info;
        }

    private:
        BaseReader &reader_;
        std::vector<BaseConstInfo *> const_infos_;
    };

}
#endif //TOYJVM_CONST_POOL_H
