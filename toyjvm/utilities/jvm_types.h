//
// Created by cyhone on 18-2-8.
//

#ifndef TOYJVM_TYPES_H
#define TOYJVM_TYPES_H

#include <cstdint>
#include <vector>
#include <memory>

namespace jvm {
    using u8 = uint64_t;
    using u4 = uint32_t;
    using u2 = uint16_t;
    using u1 = uint8_t;
    using bytes = std::vector<u1>;

    using jfloat = float;
    using jdouble = double;
    using jint = int32_t;
    using jchar = char;
    using jbyte = uint8_t;
    using jlong = int64_t;
    using jshort = short;
    using jbool = int32_t;

    class JvmRef;

    class JvmObject;

    class JvmBaseArray;

    using jref = std::shared_ptr<JvmRef>;
    using jobj = std::shared_ptr<JvmObject>;
    using jarr = std::shared_ptr<JvmBaseArray>;

}
#endif //TOYJVM_TYPES_H
