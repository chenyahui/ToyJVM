//
// Created by cyhone on 18-2-10.
//

#ifndef TOYJVM_IOUTILS_H
#define TOYJVM_IOUTILS_H

#include <string>
#include <functional>
#include "jvm_types.h"

namespace jvm {
    std::string RelativeToAbsolute(const std::string &path);

    bytes ReadFileToBytes(const std::string filename);

    bool FileExists(const std::string &filename);

    using WalkPathFunc = std::function<void()>;

    void WalkPath(const std::string &path, WalkPathFunc walkFn);
}
#endif //TOYJVM_IOUTILS_H
