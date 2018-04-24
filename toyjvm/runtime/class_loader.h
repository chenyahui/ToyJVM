//
// Created by cyhone on 18-4-19.
//

#ifndef TOYJVM_CLASS_LOADER_H
#define TOYJVM_CLASS_LOADER_H

#include <boost/noncopyable.hpp>
#include <toyjvm/classpath/class_path.h>
#include <unordered_map>
#include <toyjvm/utilities/singleton.h>

namespace jvm {
    class JvmClass;

    void prepareClass(JvmClass *klass);

    class ClassLoader : boost::noncopyable {
    public:
        ClassLoader() = default;

        void init(const std::string &jre_option, const std::string &cp_option)
        {
            class_path_ = std::make_shared<ClassPath>(jre_option, cp_option);
        }

        std::shared_ptr<JvmClass> loadClass(const std::string &class_name);

    private:
        std::shared_ptr<JvmClass> loadNonArrayClass(const std::string &class_name);

        std::shared_ptr<JvmClass> defineClass(bytes class_bytes);

    private:
        std::unordered_map<std::string, std::shared_ptr<JvmClass>> class_map_;
        std::shared_ptr<ClassPath> class_path_;
    };

    using Loader = Singleton<ClassLoader>;

}
#endif //TOYJVM_CLASS_LOADER_H
