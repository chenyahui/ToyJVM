#ifndef TOYJVM_RTDATA_CLASS_LOADER_H
#define TOYJVM_RTDATA_CLASS_LOADER_H

#include <jvm/classpath/classpath.h>
#include <jvm/rtdata/jvm_class.h>
#include <string>
#include <unordered_map>

namespace cyh {
class ClassLoader {
public:
    ClassLoader()
	: class_path_(new ClassPath())
    {
    }
    JClass* LoadClass(std::string class_name);

private:
    JClass* LoadNoArrayClass(std::string class_name);
    JClass* defineClass(const bytes& data);
    void Link(JClass* jclass);
    void Verify(JClass* jclass);
    void Prepare(JClass* jclass);

    std::unordered_map<std::string, JClass*> class_map_;
    ClassPath* class_path_;
};
}

#endif /* end of include guard: TOYJVM_RTDATA_CLASS_LOADER_H */
