#include <iostream>
#include <log.h>

#include "cmd.h"
#include "util/commonutils.h"
#include "classpath/classpath.h"

namespace cyh {
    void startJVM(cyh::CmdParser cmdParser) {
        ClassPath classPath;
        try {
            classPath.parse(cmdParser.xjreOption(), cmdParser.cpOption());
            println("classpath ", classPath.toString(), " class ", cmdParser.getClassName());

            auto className = boost::replace_all_copy(cmdParser.getClassName(), ".", "/");

            Bytes classData = classPath.readClass(className);
            print(classData.size());
            for (auto item:classData) {
                cyh::print(int(item), " ");
            }
            println("\n");

        } catch (std::exception e) {
            Log::f("出错了" + std::string(e.what()));
        }

    }
}


int main(int argc, char *argv[]) {
    cyh::CmdParser cmdParser = cyh::CmdParser(argc, argv);
    if (cmdParser.isVersion()) {
        cyh::printVersion();
    } else {
        cyh::startJVM(cmdParser);
    }


    return 0;
}



