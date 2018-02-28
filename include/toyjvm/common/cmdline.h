//
// Created by cyhone on 18-2-8.
//

#ifndef TOYJVM_CMDLINE_H
#define TOYJVM_CMDLINE_H

#include <gflags/gflags.h>
#include <string>

namespace jvm {
    struct CmdArgs {
        std::string class_path;
        std::string xjre_option;
        std::string class_name;
    };

    CmdArgs ParseCmd(int argc, char *argv[]);
}
#endif //TOYJVM_CMDLINE_H
