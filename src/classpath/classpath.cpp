//
// Created by cyhone on 17-2-25.
//


#include <stdlib.h>
#include <log.h>
#include "classpath/classpath.h"
#include "util/fileutils.h"
#include "classpath/entry_impls.h"
#include "util/commonutils.h"

using std::exception;
namespace cyh {
    Bytes ClassPath::
    readClass(std::string className) {
        className = className + ".class";
        Bytes classBytes;

        try {
            return classBytes = bootClassPath->readClass(className);
        } catch (exception e) {
            println(e.what());
        }

        try {
            return classBytes = extClassPath->readClass(className);

        } catch (exception e) {
            println(e.what());
        }

        try {
            return userClassPath->readClass(className);
        } catch (boost::filesystem::filesystem_error e) {
            Log::e(e.what());
            throw "error occured when read class file ";
        }
    }

    void ClassPath::
    parse(std::string jreOPtion, std::string cpOption) {

        parseBootAndExtClasspath(jreOPtion);

        parseUserClasspath(cpOption);

    }

    void ClassPath::
    parseBootAndExtClasspath(std::string jreOPtion) {
        std::string jreDir = getJreDir(jreOPtion);

        //  jre/lib/*
        std::string jreLibPath = FileUtils::join({jreDir, "lib", "*",});
        bootClassPath = new WildcardEntry(jreLibPath);
        std::string extLibPath = FileUtils::join({jreDir, "lib", "ext", "*",});
        extClassPath = new WildcardEntry(extLibPath);

    }

    void ClassPath::
    parseUserClasspath(std::string cpOption) {
        userClassPath = newEntry(cpOption.length() == 0 ? "." : cpOption);
    }

    std::string ClassPath::
    getJreDir(std::string jreOption) {
        if (!jreOption.length() == 0 && FileUtils::isExists(jreOption)) {
            return jreOption;
        }

        if (FileUtils::isExists("./jre")) {
            return "./jre";
        }

        auto JAVA_HOME = getEnv("JAVA_HOME");
        if (JAVA_HOME != "") {
            return FileUtils::join({JAVA_HOME, "jre"});
        }
        throw "Can not find jre folder!";
    }

    std::string ClassPath::
    toString() {
        return userClassPath->toString();
    }

}

