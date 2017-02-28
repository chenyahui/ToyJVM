//
// Created by cyhone on 17-2-26.
//

#include "util/stringutils.h"
#include <boost/algorithm/string.hpp>

using namespace boost::algorithm;
namespace cyh {
    bool StringUtils::
    exists(std::string str, std::string substr) {
        return str.find(substr) != std::string::npos;
    }


    bool StringUtils::
    exists(std::string str, char ch) {
        return str.find(ch) != std::string::npos;
    }

    bool StringUtils::
    endsWith(std::string str, char ch) {
        return str[str.length() - 1] == ch;
    }

    bool StringUtils::
    endsWith(std::string str, std::string suffix) {
        return ends_with(str, suffix);
    }
}