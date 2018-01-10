#ifndef TOYJVM_RTDATA_ACCESS_FLAG_H
#define TOYJVM_RTDATA_ACCESS_FLAG_H
#include <jvm/utils/types.h>
namespace cyh {
enum class ACC_FIELD {
    PUBLIC = 0X0001,
    PRIVATE = 0X0002,
    PROTECTED = 0X0004,
    STATIC = 0X0008,
    FINAL = 0X0010,
    VOLATILE = 0X0040,
    TRANSIENT = 0X0080,
    SYNTHETIC = 0X1000,
    ENUM = 0X4000,
};

enum class ACC_METHOD {
    PUBLIC = 0X0001,
    PRIVATE = 0X0002,
    PROTECTED = 0X0004,
    STATIC = 0X0008,
    FINAL = 0X0010,
    SYNCHRONIZED = 0x0020,
    BRIDGE = 0X0040,
    VARARGS = 0X0080,
    NATIVE = 0X0100,
    ABSTRACT = 0X0400,
    STRICT = 0X0800,
    SYNTHETIC = 0X1000,
};

enum class ACC_CLASS {
    PUBLIC = 0X0001,
    FINAL = 0X0010,
    SUPER = 0X0020,
    INTERFACE = 0X0200,
    ABSTRACT = 0X0400,
    SYNTHETIC = 0X1000,
    ANNOTATION = 0X2000,
    ENUM = 0X4000,
};

template <typename T>
bool CheckAccess(u2 access_flag, T mask)
{
    return 0 != (access_flag & static_cast<int>(mask));
}

inline bool CheckIsPublic(u2 access_flag)
{
    return CheckAccess(access_flag, ACC_CLASS::PUBLIC);
}
}

#endif /* end of include guard: TOYJVM_ACCESS_FLAG_H */
