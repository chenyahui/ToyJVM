//
// Created by cyhone on 18-2-11.
//
//
#include <toyjvm/classpath/class_path.h>
#include <toyjvm/common/ioutils.h>
#include <toyjvm/common/strutils.h>
#include <functional>

namespace jvm {
    bytes DirPathEntry::ReadClass(const std::string &class_name)
    {
        auto filename = abs_path_ + "/" + class_name;
        return ReadFileToBytes(filename);
    }

    bytes ZipPathEntry::ReadClass(const std::string &class_name)
    {
       /* bytes result;
        libzippp::ZipArchive zf(class_name);
        zf.open(libzippp::ZipArchive::READ_ONLY);

        auto entries = zf.getEntries();
        for (auto it = entries.begin(); it != entries.end(); ++it) {
            libzippp::ZipEntry entry = *it;
            if (entry.getName() == class_name) {
                int size = entry.getSize();
                auto data = reinterpret_cast<u1 *>(entry.readAsBinary());
                result.reserve(size);
                for (int i = 0; i < size; i++, data++) {
                    result.push_back(*data);
                }
                break;
            }
        }

        zf.close();
        return result;*/
		return bytes();
    }

    CompositePathEntry::CompositePathEntry(const std::string &path_list)
    {
        for (auto &path: split(path_list, ';')) {
            entrys_.push_back(PathEntryFactory(path));
        }
    }

    bytes CompositePathEntry::ReadClass(const std::string &class_name)
    {
        for (auto entry: entrys_) {
            try {
                return entry->ReadClass(class_name);
            } catch (...) {
            }
        }
    }

	void walk_test()
	{

	}

    WildCardPathEntry::WildCardPathEntry(const const std::string &path)
    {
        auto base_dir = path.substr(0, path.size() - 1);
        WalkPath(base_dir, std::bind(walk_test));
    }


    BasePathEntry *PathEntryFactory(const std::string &class_path)
    {
        if (class_path.find(';') != std::string::npos) {
            return new CompositePathEntry(class_path);
        }

        if (ends_with(class_path, "*")) {
            return new WildCardPathEntry(class_path);
        }

        if (ends_with(class_path, ".jar") || ends_with(class_path, ".JAR")
            || ends_with(class_path, ".zip") || ends_with(class_path, ".ZIP")) {
            return new ZipPathEntry(class_path);
        }

        return new DirPathEntry(class_path);
    }

}