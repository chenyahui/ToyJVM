#ifndef MY_JVM_UTILS_UTF8UTILS_H
#define MY_JVM_UTILS_UTF8UTILS_H

#include <glog/logging.h>
#include <jvm/utils/bitutils.h>
#include <jvm/utils/logutils.h>
#include <jvm/utils/types.h>
#include <sstream>
#include <string>

namespace cyh {

// modified-utf8 to c++ string
inline std::string MUtf8ToString(bytes& data)
{
    std::stringstream result;
    bool flag = true;
    for (size_t i = 0; i < data.size(); i++) {
	auto item = data[i];
	if (item <= 127) {
	    // ascii
	    flag = false;
	    result << char(item);
	} else if (item == 0xC0 && i + 1 < data.size() && data[i + 1] == 0x80) {
	    i++;
	    result << char(0);
	} else {
	    DLOG(INFO) << "尚不可解析的字符:" << int(item);
	}
    }

    return result.str();
}
}
#endif
