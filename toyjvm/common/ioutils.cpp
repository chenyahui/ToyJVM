//
// Created by cyhone on 18-2-10.
//
#include <toyjvm/common/ioutils.h>
#include <fstream>
#include <functional>
#include <boost/filesystem.hpp>
#include <iostream>

namespace bfs = boost::filesystem;
namespace jvm {

    bytes ReadFileToBytes(const std::string &filename) {
        std::ifstream file(filename, std::ifstream::binary);

        bytes data;
        char c = '\0';
        while (file.read(&c, 1)) {
            data.push_back(reinterpret_cast<u1 &>(c));
        }

        file.close();
        return data;
    }

    void walkDir(const std::string &base_path, const WalkPathFunc &walk_func) {
        auto iter = bfs::recursive_directory_iterator(bfs::path(base_path));
        bfs::recursive_directory_iterator iter_end;

        while (iter != iter_end) {
            walk_func(iter->path());
            ++iter;
        }
    }
}
