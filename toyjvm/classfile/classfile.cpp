//
// Created by cyhone on 18-2-8.
//
#include <toyjvm/utilities/bytereader.h>
#include <toyjvm/classfile/classfile.h>
#include <toyjvm/utilities/exception.h>
#include <glog/logging.h>
#include <boost/format.hpp>

using namespace jvm;

#define JAVA_CLASSFILE_MAGIC 0xCAFEBABE
#define JAVA_MIN_SUPPORTED_MAJOR_VERSION 45
#define JAVA_MAX_SUPPORTED_MAJOR_VERSION 52
#define JAVA_MAX_SUPPORTED_MINOR_VERSION 0

ClassFile::~ClassFile()
{
    for (auto field : fields_) {
        delete field;
    }

    for (auto method: methods_) {
        delete method;
    }
}

void ClassFile::parse()
{
    checkMagicAndVersions();
    const_pool_.read(reader_);
    access_flags_ = reader_.read<u2>();
    this_class_ = reader_.read<u2>();
    super_class_ = reader_.read<u2>();
    interfaces_ = reader_.batchRead<u2, u2>();
    fields_ = readMembers<FieldInfo>();
    methods_ = readMembers<MethodInfo>();
    attr_table_.read(reader_, const_pool_);

    //logClassInfo();
}

void ClassFile::logClassInfo()
{
    DLOG(INFO) << "class name : " << const_pool_.classNameOf(this_class_);
    DLOG(INFO) << "super class : " << const_pool_.classNameOf(super_class_);
    DLOG(INFO) << "interfaces : ";
    for (auto inter : interfaces_) {
        DLOG(INFO) << const_pool_.classNameOf(inter);
    }

    DLOG(INFO) << "fields count: " << fields_.size();
    for (auto &f : fields_) {
        DLOG(INFO) << f->memberName();
    }

    DLOG(INFO) << "methods count: " << fields_.size();
    for (auto &m : methods_) {
        DLOG(INFO) << m->memberName();
    }
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
        throw ClassFormatError(
                (boost::format("Unsupported version: %1%.%2%,")
                 % major_version
                 % minor_version).str()
        );
    }

    DLOG(INFO) << "version: " << major_version << "." << minor_version;
}

