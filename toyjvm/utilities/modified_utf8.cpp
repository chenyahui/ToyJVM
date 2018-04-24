//
// Created by cyhone on 18-4-14.
//

#include <toyjvm/utilities/modified_utf8.h>

namespace jvm {
    std::string parseMutf8AsString(bytes &raw_data)
    {
        std::string str(raw_data.begin(), raw_data.end());
        return str;
    }
}