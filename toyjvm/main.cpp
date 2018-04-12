//
// Created by cyhone on 18-2-9.
//
#include <toyjvm/common/cmdline.h>
#include <toyjvm/main.h>
#include <iostream>
#include <toyjvm/classpath/class_path.h>

namespace jvm {
    void startJVM(CmdArgs &args) {
        ClassPath class_path(args.xjre_option, args.class_path);
        auto class_bytes = class_path.readClass(args.class_name);
        std::cout << class_bytes.size() << std::endl;
    }
}

int main(int argc, char *argv[]) {
    auto cmd_args = jvm::parseCmd(argc, argv);
    jvm::startJVM(cmd_args);
    return 0;
}