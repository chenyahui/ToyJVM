//
// Created by cyhone on 18-2-8.
//

#ifndef TOYJVM_ATTRIBUTE_INFOS_H
#define TOYJVM_ATTRIBUTE_INFOS_H

#include <string>
#include "const_pool.h"
#include <boost/noncopyable.hpp>

namespace jvm {
    class BaseAttrInfo : boost::noncopyable {
    public:
        BaseAttrInfo(const std::string &attr_type, ConstPool *const_pool)
                : attr_type_(attr_type), const_pool_(const_pool)
        {}

        virtual void Read()
        {}

        virtual ~BaseAttrInfo()
        {}

    protected:
        std::string attr_type_;
        ConstPool *const_pool_;
    };

    class AttrConstValue : public BaseAttrInfo {
    public:
        AttrConstValue(ConstPool *const_pool) : BaseAttrInfo("ConstantValue", const_pool)
        {
        }
    public:

    };
}
#endif //TOYJVM_ATTRIBUTE_INFOS_H
