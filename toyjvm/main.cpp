//
// Created by cyhone on 18-2-9.
//
#include <toyjvm/utilities/cmdline.h>
#include <toyjvm/main.h>
#include <iostream>
#include <toyjvm/classpath/class_path.h>
#include <toyjvm/utilities/exception.h>
#include <toyjvm/classfile/classfile.h>
#include <utility>

namespace jvm {
    void startJVM(CmdArgs &args)
    {
        ClassPath class_path(args.xjre_option, args.class_path);
        try {
            auto class_name = args.class_name;
            std::replace(class_name.begin(), class_name.end(), '.', '/');
            auto class_bytes = class_path.readClass(class_name);
            ClassFile classFile(std::move(class_bytes));
            classFile.parse();
        } catch (ClassNotFound &e) {
            std::cout << e.what() << std::endl;
        }
    }

}

int main(int argc, char *argv[])
{
    //google::InitGoogleLogging(argv[0]);
    auto cmd_args = jvm::parseCmd(argc, argv);
    jvm::startJVM(cmd_args);
    return 0;
}