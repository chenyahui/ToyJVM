//
// Created by cyhone on 18-2-10.
//

#ifndef TOYJVM_PATH_ENTRY_H
#define TOYJVM_PATH_ENTRY_H

#include <toyjvm/common/uncopyable.h>
#include <toyjvm/common/jvm_types.h>
#include <string>

namespace jvm {
    class BasePathEntry : UnCopyable {
    public:
        virtual bytes ReadClass(const std::string &class_name) = 0;

        virtual ~BasePathEntry()
        {}
    };

    class DirPathEntry : public BasePathEntry {
    public:
        explicit DirPathEntry(const std::string &abs_path)
                : abs_path_(abs_path)
        {}

        bytes ReadClass(const std::string &class_name) override;

    private:
        std::string abs_path_;
    };

    class ZipPathEntry : public BasePathEntry {
    public:
        explicit ZipPathEntry(const std::string &abs_path)
                : abs_path_(abs_path)
        {}

        bytes ReadClass(const std::string &class_name) override;

    private:
        std::string abs_path_;
    };

    class CompositePathEntry : public BasePathEntry {
    public:
        explicit CompositePathEntry(const std::string &);

        bytes ReadClass(const std::string &class_name) override;

    private:
        std::vector<BasePathEntry *> entrys_;
    };

    class WildCardPathEntry : public BasePathEntry {
    public:
        explicit WildCardPathEntry(const const std::string &);

    private:
        void walk()
        {

        }
		bytes ReadClass(const std::string &class_name) override;
        std::vector<BasePathEntry *> entrys_;
    };

    BasePathEntry *PathEntryFactory(const std::string &class_path);

}

#endif //TOYJVM_PATH_ENTRY_H
