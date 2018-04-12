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

        bytes readClass(const std::string &class_name);

        ~ClassPath()
        {
            delete bootPath_;
            delete extPath_;
            delete userPath_;
        }

    private:
        void parseBootAndExtClassPath(const std::string &jre_option);

        void parseUserClassPath(const std::string &class_path);

        WildCardPathEntry *bootPath_;
        WildCardPathEntry *extPath_;
        BasePathEntry *userPath_;
    };
}
#endif //TOYJVM_PATH_ENTRY_H
