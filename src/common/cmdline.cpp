//
// Created by cyhone on 18-2-8.
//
#include <iostream>
#include <toyjvm/common/cmdline.h>
#include <boost/program_options.hpp>

namespace jvm {
    po::options_description CmdParser::opts = CmdParser::init_options();
    std::string CmdParser::classpath;

    CmdArgs CmdParser::parse(int argc, char **argv) {
        po::variables_map vm;
        po::store(po::command_line_parser(argc, argv)
                          .options(opts)
                          .style(po::command_line_style::unix_style |
                                 po::command_line_style::allow_long_disguise)
                          .run(),
                  vm);
        po::notify(vm);
        return {"", "", ""};
    }

}

