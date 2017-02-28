//
// Created by cyh on 17-2-22.
//

#pragma once

#include "entry.h"


namespace cyh {
    class ClassPath {
    private:
        Entry* bootClassPath;
        Entry* extClassPath;
        Entry* userClassPath;
    public:
        void parse(std::string jreOPtion, std::string cpOption);

        void parseBootAndExtClasspath(std::string jreOPtion);

        void parseUserClasspath(std::string cpOption);

        std::string getJreDir(std::string jreOption);

        Bytes readClass(std::string classname);

        std::string toString();
    };
}


