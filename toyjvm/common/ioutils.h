//
// Created by cyhone on 18-2-10.
//

#ifndef TOYJVM_IOUTILS_H
#define TOYJVM_IOUTILS_H

#include <string>
#include <functional>
#include <toyjvm/common/jvm_types.h>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>

namespace jvm {

    jvm::bytes ReadFileToBytes(const std::string &filename);

    using WalkPathFunc = std::function<void(const boost::filesystem::path &)>;

    void walkDir(const std::string &path, const WalkPathFunc &walk_func);
}
#endif //TOYJVM_IOUTILS_H
