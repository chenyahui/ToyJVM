//
// Created by cyhone on 18-2-8.
//
#include <iostream>
#include "toyjvm/common/cmdline.h"
namespace jvm {

    DEFINE_string(cp, "", "class path");
    DEFINE_string(xjre, "", "xjre path");

    CmdArgs ParseCmd(int argc, char *argv[])
    {


        gflags::SetVersionString("v0.1");
        gflags::SetUsageMessage("Usage : ./toyjvm");

        gflags::ParseCommandLineFlags(&argc, &argv, true);

        if (argc == 1) {
            gflags::ShowUsageWithFlags(reinterpret_cast<const char *>(argv));
            exit(0);
        }

        return {FLAGS_cp, FLAGS_xjre, argv[1]};
    }
}

