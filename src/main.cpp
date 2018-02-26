//
// Created by cyhone on 18-2-9.
//
#include "toyjvm/common/cmdline.h"
#include "toyjvm/main.h"
#include <iostream>

namespace jvm {
    void StartJVM(CmdArgs & args)
    {
        std::cout << "start jvm ..." << std::endl;
    }
}

int main(int argc, char *argv[])
{
    auto cmd_args = jvm::ParseCmd(argc, argv);
    jvm::StartJVM(cmd_args);

    return 0;
}