#ifndef CLASSFILE_H
#define CLASSFILE_H

#include <string>
#include <vector>

#include <jvm/classfile/attribute_table.h>
#include <jvm/classfile/classreader.h>
#include <jvm/classfile/constant_pool.h>
#include <jvm/classfile/member_info.h>
#include <jvm/utils/types.h>

namespace cyh {
class ClassFile {
public:
    ClassFile(bytes data);
    ~ClassFile() {}
    void Parse();
    bool CheckFormat();

    // getter
    u2 AccessFlags();
    std::string ClassName();
    std::string SuperClassName();
    std::vector<std::string> InterfaceNames();
    std::vector<std::string> FieldNames();
    std::vector<std::string> MethodNames();

private:
    void CheckMagicAndVersions();
    std::vector<MemberInfo*> ReadMembers();
    void ReadAttributes();

private:
    ConstantPool constant_pool;
    u2 access_flags;
    u2 this_class;
    u2 super_class;
    std::vector<MemberInfo*> fields;
    std::vector<MemberInfo*> methods;
    std::vector<u2> interfaces;
    AttributeTable attribute_table;
    ClassReader reader;
};

} /* classfile */

#endif /* CLASSFILE_H */
