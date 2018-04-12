//
// Created by cyhone on 18-2-11.
//
//
#include <toyjvm/classpath/class_path.h>
#include <toyjvm/common/ioutils.h>
#include <boost/algorithm/string.hpp>
#include <toyjvm/common/exception.h>
#include <zip.h>
#include <iostream>

using namespace std::placeholders;
namespace jvm {
    jvm::bytes DirPathEntry::ReadClass(const std::string &class_name)
    {
        auto class_path = absDirPath_ / class_name;
        // 能否使用std::move优化
        return ReadFileToBytes(class_path.filename().string());
    }

    jvm::bytes ZipPathEntry::ReadClass(const std::string &class_name)
    {
        struct zip *za;
        int err;
        char buf[100];
        const auto archive = absZipPath_.c_str();

        if ((za = zip_open(archive, 0, &err)) != NULL) {
            struct zip_stat zs;
            auto file_num = zip_get_num_entries(za, 0);
            for (int i = 0; i < file_num; i++) {

                if (zip_stat_index(za, i, 0, &zs) == 0
                    && strcmp(class_name.c_str(),zs.name) == 0) {

                    auto zf = zip_fopen_index(za, i, 0);
                    if (zf == NULL) {
                        continue;
                    }

                    jvm::bytes result(zs.size);
                    int sum = 0;
                    while (sum != zs.size) {
                        int len = zip_fread(zf, buf, 100);
                        std::copy(buf, buf + len, result.begin() + sum);
                        sum += len;
                    }
                    zip_fclose(zf);
                    return result;
                }
            }
        }
        zip_close(za);
        throw ClassNotFound(class_name);
    }

    CompositePathEntry::CompositePathEntry(const std::string &path_list)
    {
        std::vector<std::string> path_vec;
        boost::split(path_vec, path_list, boost::is_any_of(";"));
        for (const auto &path: path_vec) {
            entrys_.push_back(pathEntryFactory(path));
        }
    }

    jvm::bytes CompositePathEntry::ReadClass(const std::string &class_name)
    {
        for (auto entry: entrys_) {
            try {
                return entry->ReadClass(class_name);
            } catch (ClassNotFound &) {
            }
        }
        throw ClassNotFound(class_name);
    }


    WildCardPathEntry::WildCardPathEntry(const std::string &path)
            : CompositePathEntry()
    {
        auto base_dir = path.substr(0, path.size() - 1); // remove *
        walkDir(base_dir, [this](const boost::filesystem::path &file_path) {
            if (boost::filesystem::is_regular_file(file_path)) {
                auto &filename = file_path.filename().string();
                if (boost::iends_with(filename, ".jar")) {
                    this->entrys_.push_back(new ZipPathEntry(file_path));
                }
            }
        });
    }

    BasePathEntry *pathEntryFactory(const std::string &class_path)
    {
        if (class_path.find(';') != std::string::npos) {
            return new CompositePathEntry(class_path);
        }

        if (boost::ends_with(class_path, "*")) {
            return new WildCardPathEntry(class_path);
        }

        auto abs_path = bfs::absolute(class_path);
        if (bfs::exists(abs_path)) {
            return nullptr;
        }
        if (boost::iends_with(class_path, ".jar") || boost::iends_with(class_path, ".zip")) {
            return new ZipPathEntry(abs_path);
        }

        return new DirPathEntry(abs_path);
    }

}