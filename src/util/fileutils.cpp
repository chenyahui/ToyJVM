//
// Created by cyhone on 17-2-26.
//

#include "util/fileutils.h"
#include <boost/filesystem.hpp>
#include <util/commonutils.h>

using namespace boost::filesystem;

namespace cyh {
    const std::string FileUtils::PATH_LIST_SEPARATOR = ":";
    const std::string FileUtils::PATH_SEPARATOR = "/";

    bool FileUtils::
    isExists(std::string filename) {
        return boost::filesystem::exists(filename);
    }

    Bytes FileUtils::
    readFileToBytes(std::string filename) {

        std::ifstream ifs(filename, std::ios::binary | std::ios::ate);
        std::ifstream::pos_type pos = ifs.tellg();

        Bytes result(pos);
        ifs.seekg(0, std::ios::beg);
        ifs.read((char *) &result[0], pos);

        return result;
    }

    std::string FileUtils::
    join(std::vector<std::string> paths) {
        std::string result = "";

        for (int i = 0; i < paths.size(); ++i) {
            result += paths[i] + PATH_SEPARATOR;
        }

        return result.substr(0, result.length() - PATH_SEPARATOR.length());
    }

    Bytes FileUtils::
    readStringToBytes(std::string content) {

        return Bytes(content.begin(), content.end());
    }

}
