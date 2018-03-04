//
// Created by cyhone on 18-2-11.
//
//
#include <toyjvm/classpath/class_path.h>
#include <toyjvm/common/ioutils.h>
#include <functional>
#include <libzippp/libzippp.h>
#include <boost/algorithm/string.hpp>

namespace jvm {
    jvm::bytes DirPathEntry::ReadClass(const std::string &class_name) {
        auto class_path = absDirPath_ / class_name;
        // 能否使用std::move优化
        return ReadFileToBytes(class_path.filename().string());
    }

    jvm::bytes ZipPathEntry::ReadClass(const std::string &class_name) {

        bytes result;
        libzippp::ZipArchive zf(class_name);
        zf.open(libzippp::ZipArchive::READ_ONLY);

        auto entries = zf.getEntries();
        for (const auto &entry: entries) {
            if (entry.getName() == class_name) {
                auto size = entry.getSize();
                auto data = reinterpret_cast<u1 *>(entry.readAsBinary());
                result.reserve(size);
                for (int i = 0; i < size; i++, data++) {
                    result.push_back(*data);
                }
                return result;
            }
        }
        // todo throw 'class not found' exception
        throw "class not found";
    }

    CompositePathEntry::CompositePathEntry(const std::string &path_list) {
        std::vector<std::string> path_vec;
        boost::split(path_vec, path_list, ';');
        for (const auto &path: path_vec) {
            entrys_.push_back(PathEntryFactory(path));
        }
    }

    jvm::bytes CompositePathEntry::ReadClass(const std::string &class_name) {
        for (auto entry: entrys_) {
            try {
                return entry->ReadClass(class_name);
            } catch (...) {
                // to catch class not found
            }
        }

        // todo throw class not found
    }

    WildCardPathEntry::WildCardPathEntry(const const std::string &path) {
        auto base_dir = path.substr(0, path.size() - 1); // remove *

        auto walk_func = std::bind([](const boost::filesystem::path &file_path) {
            if (boost::filesystem::is_regular_file(file_path)) {
                auto &filename = file_path.filename().string();
                if (boost::iends_with(filename, ".jar")) {
                    entrys_.push_back(new ZipPathEntry(filename));
                }
            }
        });

        walkDir(base_dir, walk_func);
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