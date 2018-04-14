//
// Created by cyhone on 18-4-14.
//

#ifndef TOYJVM_MODIFY_UTF8_H
#define TOYJVM_MODIFY_UTF8_H

#include <string>
#include <toyjvm/common/jvm_types.h>

namespace jvm {
    std::string parseMutf8AsString(bytes &data);
}
#endif //TOYJVM_MODIFY_UTF8_H
