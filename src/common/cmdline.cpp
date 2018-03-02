//
// Created by cyhone on 18-2-8.
//
#include <iostream>
#include <toyjvm/common/cmdline.h>
#include <boost/program_options.hpp>

namespace po = boost::program_options;

namespace jvm {
    CmdArgs ParseCmd(int argc, char *argv[]) {
        // 应该做一个static的优化
        po::options_description opts("ToyJVM options");
        opts.add_options()
                ("classpath,cp", "the file name which want to be found")
                ("help", "this is a program to find a specified file");

        po::variables_map vm;
        store(po::parse_command_line(argc, argv, opts), vm);

        std::cout << opts << std::endl;

        return {"", "", argv[0]};
    }
}

