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

    class CmdParser : boost::noncopyable {
    public:

        CmdParser() = delete;

        static CmdArgs parse(int argc, char *argv[]);

    public:
        static po::options_description init_options() noexcept {
            po::options_description opts;
            opts.add_options()
                    ("cp", po::value<std::string>(&classpath), "<class search path of directories and zip/jar files>")
                    ("classpath", po::value<std::string>(&classpath),
                     "<class search path of directories and zip/jar files>")
                    ("help,h", "help info")
                    ("version", "print product version and exit");
            return opts;
        }

    private:
        static po::options_description opts;
        static std::string classpath;
    };

}
#endif //TOYJVM_CMDLINE_H
