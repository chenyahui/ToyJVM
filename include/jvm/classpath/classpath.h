#ifndef TOYJVM_CLASSPATH_CLASSPATH_H
#define TOYJVM_CLASSPATH_CLASSPATH_H

#include <jvm/classpath/base_entry.h>
#include <jvm/utils/types.h>
namespace cyh {
class ClassPath {
public:
    ClassPath() {}
    void parse();
    bytes ReadClass(std::string class_name);

private:
    BaseEntry* boot_class_path_;
    BaseEntry* ext_class_path_;
    BaseEntry* user_class_path_;
};
}

#endif /* end of include guard: TOYJVM_CLASSPATH_CLASSPATH_H */
