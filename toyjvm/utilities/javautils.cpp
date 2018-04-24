//
// Created by cyhone on 18-4-23.
//

#include <toyjvm/utilities/javautils.h>

namespace jvm {
    std::string getPackageName(std::string &class_name)
    {
        size_t last_found = class_name.find_last_of("/");
        if (last_found == std::string::npos) {
            return "";
        }
        return class_name.substr(0, last_found);
    }

}