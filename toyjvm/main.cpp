//
// Created by cyhone on 18-2-9.
//
#include <toyjvm/common/cmdline.h>
#include <toyjvm/main.h>
#include <iostream>
#include <toyjvm/classpath/class_path.h>
#include <toyjvm/common/exception.h>

namespace jvm {
    void startJVM(CmdArgs &args)
    {
        ClassPath class_path(args.xjre_option, args.class_path);
        try {
            auto class_name = args.class_name;
            std::replace(class_name.begin(), class_name.end(), '.', '/');
            auto class_bytes = class_path.readClass(class_name);
            std::cout << class_bytes.size() << std::endl;
        } catch (ClassNotFound &e) {
            std::cout << e.what() << std::endl;
        }
    }
}

int main(int argc, char *argv[])
{
    auto cmd_args = jvm::parseCmd(argc, argv);
    jvm::startJVM(cmd_args);
    return 0;
}