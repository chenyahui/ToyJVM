//
// Created by cyhone on 17-3-3.
//

#include <classfile/constantinfo.h>
#include <classfile/cp_numeric.h>
#include <classfile/cp_utf8.h>

namespace cyh {
    ConstantInfo *newConstantInfo(Byte tag, ConstantInfo cp) {
        switch (tag) {
            case INTEGER:
                return new ConstantIntegerInfo();
            case FLOAT:
                return new ConstantFloatInfo();
            case LONG:
                return new ConstantLongInfo();
            case UTF8:
                return new ConstantUtf8Info();
            case STRING:
                return
        }
    }
}