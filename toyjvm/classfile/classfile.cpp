//
// Created by cyhone on 18-2-8.
//
#include <toyjvm/common/basereader.h>
#include <toyjvm/classfile/classfile.h>
#include <toyjvm/common/exception.h>

using namespace jvm;

#define JAVA_CLASSFILE_MAGIC 0xCAFEBABE
#define JAVA_MIN_SUPPORTED_MAJOR_VERSION 45
#define JAVA_MAX_SUPPORTED_MAJOR_VERSION 51
#define JAVA_MAX_SUPPORTED_MINOR_VERSION 0

void ClassFile::Parse()
{
    const_pool_.read();
    access_flags_ = reader_.read<u2>();
    this_class_ = reader_.read<u2>();
    super_class_ = reader_.read<u2>();
    interfaces_ = reader_.batchRead<u2, u2>();
    fields_ = readMembers();
    methods_ = readMembers();
    attr_table_.read(reader_, const_pool_);
}

std::vector<MemberInfo> ClassFile::readMembers()
{
    auto count = reader_.read<u2>();
    std::vector<MemberInfo> result(count);

    for (int i = 0; i < count; ++i) {
        MemberInfo member(const_pool_);
        member.read(reader_);
        result.push_back(std::move(member));
    }
    return result;
}


void ClassFile::checkMagicAndVersions()
{
    if (reader_.read<u4>() != JAVA_CLASSFILE_MAGIC) {
        throw ClassFormatError("Magic Number is wrong");
    }

    auto minor_version = reader_.read<u2>();
    auto major_version = reader_.read<u2>();

    if (major_version < JAVA_MIN_SUPPORTED_MAJOR_VERSION
        || major_version > JAVA_MAX_SUPPORTED_MAJOR_VERSION
        || minor_version > JAVA_MAX_SUPPORTED_MINOR_VERSION) {
        throw ClassFormatError("Unsupported version");
    }
}

