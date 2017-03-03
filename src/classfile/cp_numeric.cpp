//
// Created by cyhone on 17-3-4.
//

#include "classfile/cp_numeric.h"

/**
 * ConstantIntegerInfo implements
 */
namespace cyh {
    void ConstantIntegerInfo::readInfo(ClassReader reader) {
        uint32 val = reader.readUint32();
        this->val = (int) val;
    }

    int32_t ConstantIntegerInfo::value() {
        return this->val;
    }
}

/**
 * ConstantFloatInfo implements
 */
namespace cyh {
    void ConstantFloatInfo::readInfo(ClassReader reader) {
        uint32 val = reader.readUint32();
        this->val = (float) val;
    }

    float ConstantFloatInfo::value() {
        return this->val;
    }
}

/**
 * ConstantLongInfo implements
 */
namespace cyh {
    void ConstantLongInfo::readInfo(ClassReader reader) {
        uint64 val = reader.readUint64();
        this->val = (long) val;
    }

    long ConstantLongInfo::value() {
        return this->val;
    }
}

/**
 * ConstantDoubleInfo implements
 */
namespace cyh {
    void ConstantDoubleInfo::readInfo(ClassReader reader) {
        uint64 val = reader.readUint64();
        this->val = (double) val;
    }

    double ConstantDoubleInfo::value() {
        return this->val;
    }
}