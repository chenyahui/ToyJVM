//
// Created by cyhone on 18-4-13.
//

#ifndef TOYJVM_ATTRIBUTE_TABLE_H
#define TOYJVM_ATTRIBUTE_TABLE_H

#include <string>
#include <toyjvm/classfile/const_pool.h>
#include <toyjvm/utilities/basereader.h>
#include <toyjvm/classfile/attribute_infos.h>

namespace jvm {


    class AttrTable {
    public:
        AttrTable() = default;

        void read(BaseReader &reader, const ConstPool &);

        inline const std::vector<BaseAttrInfo *> attrInfos() const
        {
            return attr_infos_;
        }

        /*
         *  用户需要自行保证attr_type和T一致
         */
        template<typename T>
        T *getFirst(const std::string &attr_type) const
        {
            for (auto attr_info : attr_infos_) {
                if (attr_info->attrType() == attr_type) {
                    return dynamic_cast<T *>(attr_info);
                }
            }

            return nullptr;
        };

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
