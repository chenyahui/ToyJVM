//
// Created by cyhone on 18-4-13.
//

#include <toyjvm/classfile/attribute_table.h>
#include <glog/logging.h>

namespace jvm {
    void AttrTable::read(ByteReader &reader, const ConstPool &pool)
    {
        auto count = reader.read<u2>();
        attr_infos_.resize(count);
        for (int i = 0; i < count; ++i) {
            auto attr_info = readAttrInfo(reader, pool);
            attr_info->read(reader);
            attr_infos_.push_back(attr_info);
        }
    }

    BaseAttrInfo *AttrTable::readAttrInfo(ByteReader &reader, const ConstPool &const_pool)
    {
        auto attr_name_index = reader.read<u2>();
        auto attr_len = reader.read<u4>();
        auto attr_name = const_pool.stringAt(attr_name_index);
        return attrInfoFactory(attr_name, attr_len, const_pool);
    }

    BaseAttrInfo *AttrTable::attrInfoFactory(const std::string &attr_name,
                                             u4 attr_len,
                                             const jvm::ConstPool &const_pool)
    {
#define PARSE_ATTR(TAG) \
if(attr_name == #TAG){ \
    return new Attr##TAG(attr_name, const_pool); \
}
        PARSE_ATTR(BootstrapMethods)
        PARSE_ATTR(Code)
        PARSE_ATTR(ConstantValue)
        PARSE_ATTR(Deprecated)
        PARSE_ATTR(EnclosingMethod)
        PARSE_ATTR(Exceptions)
        PARSE_ATTR(InnerClasses)
        PARSE_ATTR(LineNumberTable)
        PARSE_ATTR(LocalVariableTable)
        PARSE_ATTR(LocalVariableTypeTable)
        PARSE_ATTR(Signature)
        PARSE_ATTR(SourceFile)
        PARSE_ATTR(Synthetic)

        return new AttrUnparsed(attr_name, attr_len, const_pool);
#undef PARSE_ATTR
    }
}

