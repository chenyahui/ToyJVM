#include <jvm/classfile/classfile.h>
#include <jvm/classfile/constant_infos.h>
#include <jvm/utils/fileutils.h>

using std::vector;
using std::string;

#define JAVA_CLASSFILE_MAGIC 0xCAFEBABE
#define JAVA_MIN_SUPPORTED_VERSION 45
#define JAVA_MAX_SUPPORTED_VERSION 51
#define JAVA_MAX_SUPPORTED_MINOR_VERSION 0

#include <iostream>
#include <jvm/utils/logutils.h>

namespace cyh {
ClassFile::ClassFile(bytes data)
    : reader(ClassReader(data))
{
}

u2 ClassFile::AccessFlags()
{
    return access_flags;
}

string ClassFile::ClassName()
{
    return constant_pool.GetClassName(this_class);
}

string ClassFile::SuperClassName()
{
    return constant_pool.GetClassName(super_class);
}

vector<string> ClassFile::InterfaceNames()
{
    vector<string> result;
    for (auto index : interfaces) {
	result.push_back(constant_pool.GetClassName(index));
    }

    return result;
}
vector<string> ClassFile::MethodNames()
{
    vector<string> result;
    for (auto method_info : methods) {
	result.push_back(method_info->MemberName());
    }

    return result;
}

vector<string> ClassFile::FieldNames()
{
    vector<string> result(fields.size());
    for (auto field_info : fields) {
	result.push_back(field_info->MemberName());
    }

    return result;
}

bool ClassFile::CheckFormat()
{
    return true;
}
void ClassFile::Parse()
{
    CheckMagicAndVersions();

    constant_pool.Read(reader);
    log("constant pool finish!");

    access_flags = reader.ReadU2();
    this_class = reader.ReadU2();
    super_class = reader.ReadU2();
    interfaces = reader.ReadU2s();

    log("begin read fields");
    fields = ReadMembers();
    log("begin read methods");
    methods = ReadMembers();
    log("begin read attribute_table");
    attribute_table.Read(reader, &constant_pool);
    log("classfile read finish!!!");
}

std::vector<MemberInfo*> ClassFile::ReadMembers()
{
    u2 count = reader.ReadU2();
    std::vector<MemberInfo*> result(count);

    for (int i = 0; i < count; ++i) {
	auto member = new MemberInfo(&constant_pool);
	member->Read(reader);
	result[i] = member;
    }

    return result;
}
void ClassFile::CheckMagicAndVersions()
{
    u4 magic = reader.ReadU4();
    log(magic);
    if (magic != JAVA_CLASSFILE_MAGIC) {
	throw "ClassFile Magic Number is wrong";
    }

    u2 minor_version = reader.ReadU2();
    u2 major_version = reader.ReadU2();

    log("version");
    log(minor_version);
    log(major_version);

    // TODO check versions
}
}
