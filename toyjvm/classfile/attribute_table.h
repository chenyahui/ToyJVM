//
// Created by cyhone on 18-4-13.
//

#ifndef TOYJVM_ATTRIBUTE_TABLE_H
#define TOYJVM_ATTRIBUTE_TABLE_H

#include <string>
#include <toyjvm/classfile/const_pool.h>
#include <toyjvm/common/basereader.h>

namespace jvm {
    class BaseAttrInfo;

    class AttrTable {
    public:
        AttrTable() = default;

        void read(BaseReader &reader, const ConstPool &);

    private:
        BaseAttrInfo *readAttrInfo(BaseReader &reader, const ConstPool &);

        BaseAttrInfo *attrInfoFactory(std::string &attr_name,
                                      u4 attr_len,
                                      const jvm::ConstPool &const_pool);

    private:
        std::vector<BaseAttrInfo *> attr_infos_;
    };


}
#endif //TOYJVM_ATTRIBUTE_TABLE_H
