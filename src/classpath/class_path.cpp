//
// Created by cyhone on 18-2-10.
//
#include <toyjvm/classpath/class_path.h>
#include <toyjvm/common/ioutils.h>
#include <toyjvm/common/system.h>
#include <toyjvm/common/strutils.h>

namespace jvm {
    static std::string GetJreDir(const std::string &jre_option);

    ClassPath::ClassPath(const std::string &jre_option, const std::string &cp_option)
    {
        ParseBootAndExtClassPath(jre_option);
        ParseUserClassPath(cp_option);
    }

    bytes ClassPath::ReadClass(const std::string &class_name)
    {
        auto cname = class_name + ".class";
        bytes data;
        try {
            data = boot_path_->ReadClass(cname);
        } catch (...) {
            try {
                data = ext_path_->ReadClass(cname);
            } catch (...) {
                data = user_path_->ReadClass(cname);
            }
        }

        return data;
    }

    void ClassPath::ParseBootAndExtClassPath(const std::string &jre_option)
    {
        auto jre_dir = GetJreDir(jre_option);

        boot_path_ = new WildCardPathEntry(jre_dir + "/lib/*");
        ext_path_ = new WildCardPathEntry(jre_dir + "/lib/ext/*");
    }

    void ClassPath::ParseUserClassPath(const std::string &class_path)
    {
        user_path_ = PathEntryFactory(class_path.empty() ? "." : class_path);
    }

    std::string GetJreDir(const std::string &jre_option)
    {
        if (!jre_option.empty() && FileExists(jre_option)) {
            return jre_option;
        }

        if (FileExists("./jre")) {
            return "./jre";
        }

        std::string java_home = GetEnv("JAVA_HOME");

        if (!java_home.empty()) {
            return java_home + "/" + "jre";
        }

        throw "can not find jre folder";
    }
}
