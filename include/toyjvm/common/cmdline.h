//
// Created by cyhone on 18-2-8.
//

#ifndef TOYJVM_CMDLINE_H
#define TOYJVM_CMDLINE_H

#include <gflags/gflags.h>
#include <string>
#include <boost/core/noncopyable.hpp>
#include <boost/program_options.hpp>

namespace po = boost::program_options;
namespace jvm {
    struct CmdArgs {
        std::string class_path;
        std::string xjre_option;
        std::string class_name;
    };

    CmdArgs parseCmd(int argc, char **argv);
}
#endif //TOYJVM_CMDLINE_H
