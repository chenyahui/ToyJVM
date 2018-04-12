//
// Created by cyhone on 18-2-10.
//
#include <toyjvm/classpath/class_path.h>
#include <toyjvm/common/ioutils.h>
#include <boost/filesystem.hpp>
#include <toyjvm/common/exception.h>

namespace jvm {
    static std::string GetJreDir(const std::string &jre_option);

    ClassPath::ClassPath(const std::string &jre_option, const std::string &cp_option) {
        parseBootAndExtClassPath(jre_option);
        parseUserClassPath(cp_option);
    }

    bytes ClassPath::readClass(const std::string &class_name) {
        auto cname = class_name + ".class";
        bytes data;
        try {
            data = bootPath_->ReadClass(cname);
        } catch (...) {
            try {
                data = extPath_->ReadClass(cname);
            } catch (...) {
                data = userPath_->ReadClass(cname);
            }
        }

        throw ClassNotFound();
    }

    void ClassPath::parseBootAndExtClassPath(const std::string &jre_option) {
        auto jre_dir = GetJreDir(jre_option);

        bootPath_ = new WildCardPathEntry(jre_dir + "/lib/*");
        extPath_ = new WildCardPathEntry(jre_dir + "/lib/ext/*");
    }

    void ClassPath::parseUserClassPath(const std::string &class_path) {
        if (class_path.empty()) {
            userPath_ = pathEntryFactory(".");
        } else {
            userPath_ = pathEntryFactory(class_path);
        }
    }

    std::string GetJreDir(const std::string &jre_option) {

        if (!jre_option.empty() && boost::filesystem::exists(jre_option)) {
            return jre_option;
        }

        if (boost::filesystem::exists("./jre")) {
            return "./jre";
        }

        std::string java_home = std::getenv("JAVA_HOME");
        if (!java_home.empty()) {
            return java_home + "/" + "jre";
        }

        throw JVMError("Can not find jre folder");
    }
}
