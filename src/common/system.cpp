//
// Created by cyhone on 18-2-10.
//
#include <toyjvm/common/system.h>

namespace jvm {
    std::string GetEnv(const std::string &key)
    {
        const char *val = ::getenv(key.c_str());
        if (val == 0) {
            return "";
        } else {
            return val;
        }
    }
}

