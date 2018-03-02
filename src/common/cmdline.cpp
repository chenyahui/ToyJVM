//
// Created by cyhone on 18-2-8.
//
#include <iostream>
#include <toyjvm/common/cmdline.h>
#include <boost/program_options.hpp>

namespace jvm {

    CmdArgs parseCmd(int argc, char **argv) {
        CmdArgs cmd_args;

        po::options_description opts;
        opts.add_options()
                ("cp", po::value<std::string>(&cmd_args.class_path),
                 "<class search path of directories and zip/jar files>")
                ("classpath", po::value<std::string>(&cmd_args.class_path),
                 "<class search path of directories and zip/jar files>")
                ("help,h", "help info")
                ("version", "print product version and exit");

        po::variables_map vm;
        po::store(po::command_line_parser(argc, argv)
                          .options(opts)
                          .style(po::command_line_style::unix_style |
                                 po::command_line_style::allow_long_disguise)
                          .run(),
                  vm);
        po::notify(vm);

        return cmd_args;
    }
}

