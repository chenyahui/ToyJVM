//
// Created by cyhone on 18-2-10.
//
#include <toyjvm/common/ioutils.h>
#include <fstream>
#include <functional>

namespace jvm {

    std::string RelativeToAbsolute(const std::string &path)
    {
        char *full_path = realpath(path.c_str(), NULL);

        std::string result(full_path);

        free(full_path);
        return result;
    }



    bytes ReadFileToBytes(const std::string filename)
    {
        std::ifstream file(filename, std::ifstream::binary);

        if (!file.good()) {
            throw "文件" + filename + "不存在";
        }

        bytes data;
        char c = '\0';
        while (file.read(&c, 1)) {
            data.push_back(reinterpret_cast<u1 &>(c));
        }

        file.close();
        return data;
    }
}
