#include "cmd.h"

namespace cyh {
    CmdParser::
    CmdParser() {
        init();
    }

    CmdParser::
    CmdParser(int argc, char **argv) : CmdParser() {
        parser(argc, argv);
    }

    void CmdParser::
    parser(int argc, char **argv) {
        cmdParser.parse_check(argc, argv);
        className = std::string(argv[1]);
    }

    bool CmdParser::
    isVersion() {
        return cmdParser.exist("version");
    }

    std::string CmdParser::
    xjreOption() {
        return cmdParser.get<std::string>("Xjre");
    }

    std::string CmdParser::cpOption() {
        auto result = cmdParser.get<std::string>("cp");
        return result.empty() ? cmdParser.get<std::string>("classpath") : result;
    }

    std::string CmdParser::
    getClassName() {
        return className;
    }

    void CmdParser::
    init() {
        //version
        cmdParser.add("version", '\0', "print version and exit");

        //classpath
        cmdParser.add<std::string>("classpath", '\0', "classpath", false, "");
        cmdParser.add<std::string>("cp", '\0', "classpath", false, "");

        //Xjre
        cmdParser.add<std::string>("Xjre", '\0', "path to jre", false, "");
    }

    void printVersion() {
        std::cout << "version 0.0.1" << std::endl;
    }
}

