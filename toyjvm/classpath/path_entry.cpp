//
// Created by cyhone on 18-2-11.
//
//
#include <toyjvm/classpath/class_path.h>
#include <toyjvm/common/ioutils.h>
#include <functional>
#include <boost/algorithm/string.hpp>
#include <toyjvm/common/exception.h>

namespace jvm {
    jvm::bytes DirPathEntry::ReadClass(const std::string &class_name) {
        auto class_path = absDirPath_ / class_name;
        // 能否使用std::move优化
        return ReadFileToBytes(class_path.filename().string());
    }

    jvm::bytes ZipPathEntry::ReadClass(const std::string &class_name) {

        return jvm::bytes();
    }

    CompositePathEntry::CompositePathEntry(const std::string &path_list) {
        std::vector<std::string> path_vec;
        boost::split(path_vec, path_list, boost::is_any_of(";"));
        for (const auto &path: path_vec) {
            entrys_.push_back(pathEntryFactory(path));
        }
    }

    jvm::bytes CompositePathEntry::ReadClass(const std::string &class_name) {
        for (auto entry: entrys_) {
            try {
                return entry->ReadClass(class_name);
            } catch (ClassNotFound) {
            }
        }
        throw ClassNotFound();
    }

    void WildCardPathEntry::walkHandler(const boost::filesystem::path &file_path) {
        if (boost::filesystem::is_regular_file(file_path)) {
            auto &filename = file_path.filename().string();
            if (boost::iends_with(filename, ".jar")) {
                entrys_.push_back(new ZipPathEntry(filename));
            }
        }
    }

    WildCardPathEntry::WildCardPathEntry(const std::string &path)
            : CompositePathEntry() {
        auto base_dir = path.substr(0, path.size() - 1); // remove *

        walkDir(base_dir, std::bind(&WildCardPathEntry::walkHandler,
                                    this,
                                    std::placeholders::_1));
    }

    BasePathEntry *pathEntryFactory(const std::string &class_path) {
        if (class_path.find(';') != std::string::npos) {
            return new CompositePathEntry(class_path);
        }

        if (boost::ends_with(class_path, "*")) {
            return new WildCardPathEntry(class_path);
        }

        auto abs_path = bfs::absolute(class_path);

        if (boost::iends_with(class_path, ".jar") || boost::iends_with(class_path, ".zip")) {
            return new ZipPathEntry(abs_path);
        }

        return new DirPathEntry(abs_path);
    }

}