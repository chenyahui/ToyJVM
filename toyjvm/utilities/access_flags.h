//
// Created by cyhone on 18-4-19.
//

#ifndef TOYJVM_ACCESS_FLAGS_H
#define TOYJVM_ACCESS_FLAGS_H

#include <toyjvm/utilities/jvm_types.h>

namespace jvm {
#define DEF_FLAG(NAME, FLAG) \
inline bool is##NAME() const \
{ \
    return (flags_ & FLAG##) != 0; \
}

    class AccessFlags {
    public:
        explicit AccessFlags(jint flags)
                : flags_(flags)
        {}

        enum ACC_FLAG {
            PUBLIC = 0x0001,
            PRIVATE = 0x0002,
            PROTECTED = 0x0004,
            STATIC = 0x0008,
            FINAL = 0x0010,
            SYNCHRONIZED = 0x0020,
            SUPER = 0x0020,
            VOLATILE = 0x0040,
            BRIDGE = 0x0040,
            TRANSIENT = 0x0080,
            VARARGS = 0x0080,
            NATIVE = 0x0100,
            INTERFACE = 0x0200,
            ABSTRACT = 0x0400,
            STRICT = 0x0800,
            SYNTHETIC = 0x1000,
            ANNOTATION = 0x2000,
            ENUM = 0x4000,
        };

        DEF_FLAG(Public, PUBLIC)

        DEF_FLAG(Protected, PROTECTED)

        DEF_FLAG(Private, PRIVATE)

        DEF_FLAG(Static, STATIC)

        DEF_FLAG(Final, FINAL)

        DEF_FLAG(Interface, INTERFACE)

        DEF_FLAG(Super, SUPER)

        DEF_FLAG(Abstract, ABSTRACT)

    private:
        jint flags_;
    };

#undef DEF_FLAG
}


#endif //TOYJVM_ACCESS_FLAGS_H
