#ifndef MY_JVM_UTILS_FILEUTILS_H
#define MY_JVM_UTILS_FILEUTILS_H

#include <fstream>
#include <jvm/utils/logutils.h>
#include <jvm/utils/types.h>
#include <string>

namespace cyh {
using std::ifstream;

inline bytes readfile(const std::string& filename)
{
    ifstream file(filename, ifstream::binary);
    if (!file.good()) {
	throw "文件" + filename + "不存在";
    }

    bytes data;
    char c = '\0';
    while (file.read(&c, 1)) {
	data.push_back(reinterpret_cast<u1&>(c));
    }

    file.close();
    return data;
}
}

#endif
