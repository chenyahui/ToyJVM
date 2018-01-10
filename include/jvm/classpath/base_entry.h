#ifndef TOYJVM_CLASSPATH_BASE_ENTRY_H
#define TOYJVM_CLASSPATH_BASE_ENTRY_H
#include <string>
namespace cyh {
class BaseEntry {
public:
    virtual void ReadClass(std::string classname);
};

class DirEntry : public BaseEntry {
public:
    void ReadClass(std::string) override;
};

class ZipEntry : public BaseEntry {
public:
    void ReadClass(std::string) override;
};
class CompositeEntry : public BaseEntry {
public:
    void ReadClass(std::string) override;
};
}

#endif /* end of include guard: TOYJVM_BASE_ENTRY_H */
