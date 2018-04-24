//
// Created by cyhone on 18-2-10.
//

#ifndef TOYJVM_PATH_ENTRY_H
#define TOYJVM_PATH_ENTRY_H

#include <toyjvm/utilities/jvm_types.h>
#include <string>
#include <boost/noncopyable.hpp>
#include <boost/filesystem/path.hpp>

namespace bfs = boost::filesystem;

namespace jvm {
    class BasePathEntry : boost::noncopyable {
    public:
        virtual bytes ReadClass(const std::string &class_name) = 0;

        virtual ~BasePathEntry()
        {}
    };

    // -cp /home/cyhone/com/cyhone
    class DirPathEntry : public BasePathEntry {
    public:
        explicit DirPathEntry(const bfs::path &abs_path)
                : absDirPath_(abs_path)
        {}

        bytes ReadClass(const std::string &class_name) override;

    private:
        bfs::path absDirPath_;
    };

    // -cp /home/cyhone/com.cyhone.test.jar
    class ZipPathEntry : public BasePathEntry {
    public:
        explicit ZipPathEntry(const bfs::path &abs_path)
                : absZipPath_(abs_path)
        {}

        bytes ReadClass(const std::string &class_name) override;

    private:
        bfs::path absZipPath_;
    };

    // -cp /home/cyhone/com.cyhone.test.jar;/home/cyhone/com/cyhone
    class CompositePathEntry : public BasePathEntry {
    public:
        explicit CompositePathEntry(const std::string &path_list);

        CompositePathEntry() = default;

        bytes ReadClass(const std::string &class_name) override;

    protected:
        std::vector<BasePathEntry *> entrys_;
    };

    // -cp /home/cyhone/com/cyhone/*
    class WildCardPathEntry : public CompositePathEntry {
    public:
        explicit WildCardPathEntry(const std::string &);
    };

    /**
     *
     * @param class_path
     * @return nullptr or object
     */
    BasePathEntry *pathEntryFactory(const std::string &class_path);

}

#endif //TOYJVM_PATH_ENTRY_H
