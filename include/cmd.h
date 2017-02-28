//
// Created by cyhone on 17-2-26.
//

#pragma once

#include <string>
#include "cmdline.h"

namespace cyh {
    class CmdParser {
    public:
        CmdParser();

        CmdParser(int argc, char *argv[]);

        void parser(int argc, char *argv[]);

        bool isVersion();

        std::string getClassName();

        std::string xjreOption();

        std::string cpOption();

    private:
        void init();

        cmdline::parser cmdParser;
        std::string className;
    };

    void printVersion();
}


