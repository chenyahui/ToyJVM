//
// Created by cyhone on 17-2-26.
//

#include "util/commonutils.h"
#include <cstdlib>

namespace cyh {
    std::string getEnv(std::string key) {
        char const *tmp = std::getenv(key.c_str());
        if (tmp == NULL) {
            return "";
        } else {
            return std::string(tmp);
        }
    }

    void printError(std::string msg) {
        std::cerr << msg << std::endl;
    }

    void errorAndExist(std::string msg) {
        printError(msg);
        std::terminate();
    }


}