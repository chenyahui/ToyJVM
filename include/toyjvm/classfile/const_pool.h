//
// Created by cyhone on 18-2-8.
//

#ifndef TOYJVM_CONST_POOL_H
#define TOYJVM_CONST_POOL_H

#include "toyjvm/common/basereader.h"

namespace jvm {
    class BaseConstInfo;

    class ConstPool {
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

        void Read(BaseReader &);

        BaseConstInfo *ConstInfoFactory(ConstType tag);

    private:
        std::vector<BaseConstInfo *> const_infos_;
    };

}
#endif //TOYJVM_CONST_POOL_H
