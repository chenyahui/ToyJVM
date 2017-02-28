//
// Created by cyhone on 17-2-22.
//
#include <boost/algorithm/string/join.hpp>
#include <boost/filesystem.hpp>
#include <util/commonutils.h>


#include "classpath/entry_impls.h"
#include "util/fileutils.h"
#include "libzippp/libzippp.h"
#include "exception.h"

using boost::filesystem::directory_iterator;
using boost::filesystem::path;

/**
 *  DirEntry implements
 */
namespace cyh {
    DirEntry::
    DirEntry(std::string path) {
        absDir = FileUtils::getAbsolutePath(path);
    }

    Bytes DirEntry::
    readClass(std::string className) {
        auto filename = FileUtils::join({absDir, className});
        return FileUtils::readFileToBytes(filename);
    }

    std::string DirEntry::
    toString() {
        return absDir;
    }
}

/**
 * ZipEntry implements
 */
namespace cyh {
    ZipEntry::
    ZipEntry(std::string path) {
        absPath = FileUtils::getAbsolutePath(path);
    }

    /**
     * read class
     * @param className
     * @return
     */
    Bytes ZipEntry::
    readClass(std::string className) {

        libzippp::ZipArchive zipArchive(absPath);
        zipArchive.open(libzippp::ZipArchive::READ_ONLY);

        std::vector<libzippp::ZipEntry> entries = zipArchive.getEntries();
        std::vector<libzippp::ZipEntry>::iterator it;
        for (it = entries.begin(); it != entries.end(); ++it) {
            auto entry = *it;
            std::string name = entry.getName();

            if (name == className) {

                return FileUtils::readStringToBytes(entry.readAsText());
            }
        }

        throw ClassNotFoundException("class no found");
    }

    /**
    /**
     * tostring
     * @return
     */
    std::string ZipEntry::
    toString() {
        return absPath;
    }
}

/**
 * CompositeEntry implements
 */
namespace cyh {
    CompositeEntry::
    CompositeEntry() {
    }

    CompositeEntry::
    CompositeEntry(const std::string pathList) {

        for (auto item : StringUtils::split(pathList, FileUtils::PATH_LIST_SEPARATOR)) {
            entrys.push_back(newEntry(item));
        }
    }

    Bytes CompositeEntry::
    readClass(std::string className) {
        for (auto entry:entrys) {
            try {
                return entry->readClass(className);
            } catch (...) {
                continue;
            }
        }
        throw ClassNotFoundException("class not found");
    }

    std::string CompositeEntry::
    toString() {
        std::vector<std::string> strs;
        for (auto entry:entrys) {
            strs.push_back(entry->toString());
        }
        return boost::algorithm::join(strs, FileUtils::PATH_LIST_SEPARATOR);
    }

    void CompositeEntry::
    appendEntry(Entry *entry) {
        entrys.push_back(entry);
    }
}

/**
 * WildcardEntry implements
 */
namespace cyh {
    WildcardEntry::
    WildcardEntry(std::string pathname) {

        auto baseDir = pathname.substr(0, pathname.length() - 1);

        directory_iterator end_itr;
        for (auto &entry : boost::make_iterator_range(directory_iterator(path(baseDir)), {})) {
            path file = entry.path();
            if (is_regular_file(file)) {
                std::string filename = file.filename().string();
                if (StringUtils::endsWith(filename, ".jar")
                    || StringUtils::endsWith(filename, ".JAR")) {
                    compositeEntry.appendEntry(new ZipEntry(baseDir + filename));
                }

            }
        }
    }

    std::string WildcardEntry::
    toString() {
        return compositeEntry.toString();
    }

    Bytes WildcardEntry::
    readClass(std::string className) {
        return compositeEntry.readClass(className);
    }
}