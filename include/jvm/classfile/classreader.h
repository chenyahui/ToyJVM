#ifndef MY_JVM_CLASSFILE_CLASSREADER_H
#define MY_JVM_CLASSFILE_CLASSREADER_H

#include <jvm/utils/types.h>

namespace cyh {
class ClassReader {
public:
    ClassReader(){};
    ClassReader(const ClassReader&);
    ClassReader(bytes&);
    ClassReader& operator=(const ClassReader&);
    virtual ~ClassReader();

    u8 ReadU8();
    u4 ReadU4();
    u2 ReadU2();
    std::vector<u2> ReadU2s();
    bytes ReadU1s();
    bytes ReadU1s(u4);
    u1 ReadU1();

private:
    bytes data_;
    int now_;
};
}

#endif /* ifndef  */
