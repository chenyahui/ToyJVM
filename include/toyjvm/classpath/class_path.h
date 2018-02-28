//
// Created by cyhone on 18-2-10.
//

#ifndef TOYJVM_CLASS_PATH_H
#define TOYJVM_CLASS_PATH_H

#include <toyjvm/common/jvm_types.h>
#include <string>
#include <toyjvm/classpath/path_entry.h>
#include <boost/noncopyable.hpp>

namespace jvm {
    class ClassPath : boost::noncopyable {
    public:
        ClassPath(const std::string &jre_option, const std::string &cp_option);

        bytes ReadClass(const std::string &class_name);

    private:
        void ParseBootAndExtClassPath(const std::string &jre_option);

        void ParseUserClassPath(const std::string &class_path);

        BasePathEntry *boot_path_;
        BasePathEntry *ext_path_;
        BasePathEntry *user_path_;
    };
}
#endif //TOYJVM_PATH_ENTRY_H
