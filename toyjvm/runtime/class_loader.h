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
    class JvmBaseClass;

    class JvmClass;

    class JvmArrayClass;

    void prepareClass(JvmClass *klass);

    class ClassLoader : boost::noncopyable {
    public:
        ClassLoader() = default;

        void init(const std::string &jre_option, const std::string &cp_option)
        {
            class_path_ = std::move(std::unique_ptr<ClassPath>(new ClassPath(jre_option, cp_option)));
        }

        JvmBaseClass* loadClass(const std::string &class_name);

        JvmClass* loadNonArrayClass(const std::string &class_name);

        JvmArrayClass* loadArrayClass(const std::string &class_name);

        void detailInfo();
    private:
        JvmClass *defineClass(bytes class_bytes);

    private:
        std::unordered_map<std::string, JvmClass *> non_array_class_map_;
        std::unordered_map<std::string, JvmArrayClass *> array_class_map_;
        std::unique_ptr<ClassPath> class_path_;
    };

    using Loader = Singleton<ClassLoader>;

}
#endif //TOYJVM_CLASS_LOADER_H
