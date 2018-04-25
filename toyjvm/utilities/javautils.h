//
// Created by cyhone on 18-4-23.
//

#ifndef TOYJVM_JAVAUTILS_H
#define TOYJVM_JAVAUTILS_H

#include <string>

namespace jvm {

    std::string getPackageName(const std::string &class_name);

    std::string descriptorToClassName(const std::string& descriptor);

}
#endif //TOYJVM_JAVA_UTILS_H
