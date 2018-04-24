//
// Created by cyhone on 18-2-10.
//
#include <toyjvm/classpath/class_path.h>
#include <toyjvm/utilities/ioutils.h>
#include <boost/filesystem.hpp>
#include <toyjvm/utilities/exception.h>

namespace jvm {
    static std::string GetJreDir(const std::string &jre_option);

    static std::string GetClassPath(const std::string &class_path);

    ClassPath::ClassPath(const std::string &jre_option, const std::string &cp_option)
    {
        parseBootAndExtClassPath(jre_option);
        parseUserClassPath(cp_option);
    }

    bytes ClassPath::readClass(const std::string &class_name)
    {
        auto cname = class_name + ".class";
        bytes data;
        try {
            return bootPath_->ReadClass(cname);
        } catch (...) {
            try {
                return extPath_->ReadClass(cname);
            } catch (...) {
                if (userPath_ != nullptr) {
                    return userPath_->ReadClass(cname);
                }
            }
        }

        throw ClassNotFound(class_name);
    }

    void ClassPath::parseBootAndExtClassPath(const std::string &jre_option)
    {
        auto jre_dir = GetJreDir(jre_option);

        bootPath_ = new WildCardPathEntry(jre_dir + "/lib/*");
        extPath_ = new WildCardPathEntry(jre_dir + "/lib/ext/*");
    }

    void ClassPath::parseUserClassPath(const std::string &class_path)
    {
        userPath_ = pathEntryFactory(GetClassPath(class_path));
    }

    std::string GetClassPath(const std::string &class_path)
    {
        std::string sys_class_path = std::getenv("JAVA_HOME");
        if (class_path.empty()) {
            return sys_class_path;
        }
        return sys_class_path + ";" + class_path;
    }

    std::string GetJreDir(const std::string &jre_option)
    {

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
