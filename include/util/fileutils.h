//
// Created by cyhone on 17-2-22.
//
#pragma once

#include <string>
#include <vector>
#include "types.h"
#include <boost/filesystem.hpp>

namespace cyh {
    class FileUtils {
    public:
        static bool isExists(std::string filename);

        static inline std::string getAbsolutePath(std::string filename) {
            return boost::filesystem::canonical(boost::filesystem::path(filename)).string();
        }

        static Bytes readFileToBytes(std::string filename);

        static Bytes readStringToBytes(std::string content);

        static std::string join(std::vector<std::string> paths);

        static const std::string PATH_LIST_SEPARATOR;
        static const std::string PATH_SEPARATOR;
    private:
        FileUtils() = delete;
    };


}

