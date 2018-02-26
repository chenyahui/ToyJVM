//
// Created by cyhone on 18-2-8.
//
#include <toyjvm/common/basereader.h>
#include "toyjvm/classfile/classfile.h"

using namespace jvm;

void ClassFile::Parse(bytes data)
{
    BaseReader reader(data);

    access_flags_ = reader.Read<u2>();
    this_class_ = reader.Read<u2>();
    super_class_ = reader.Read<u2>();
    interfaces = reader.BatchRead<u2, u2>();

}
