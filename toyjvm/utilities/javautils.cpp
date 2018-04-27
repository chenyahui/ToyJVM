//
// Created by cyhone on 18-4-23.
//

#include <toyjvm/utilities/javautils.h>
#include <unordered_map>

namespace jvm {
    std::string getPackageName(const std::string &class_name)
    {
        size_t last_found = class_name.find_last_of('/');
        if (last_found == std::string::npos) {
            return "";
        }
        return class_name.substr(0, last_found);
    }

    const std::unordered_map<std::string, std::string> primitiveTypes = {
            {"void",    "V"},
            {"boolean", "Z"},
            {"byte",    "B"},
            {"short",   "S"},
            {"int",     "I"},
            {"long",    "J"},
            {"char",    "C"},
            {"float",   "F"},
            {"double",  "D"}
    };

    std::string descriptorToClassName(const std::string &descriptor)
    {
        if (descriptor[0] == '[') {
            return descriptor;
        }
        if (descriptor[0] == 'L') {
            // L at begin, comma at end
            return descriptor.substr(1, descriptor.size() - 2);
        }

        for (auto &kv : primitiveTypes) {
            if (kv.second == descriptor) {
                return kv.first;
            }
        }
        return "";
    }

    std::string classNameToDescriptor(const std::string &class_name)
    {
        if (class_name[0] == '[') {
            return class_name;
        }

        auto data = primitiveTypes.find(class_name);
        if (data != primitiveTypes.end()) {
            return data->second;
        }

        return "L" + class_name + ";";
    }


}