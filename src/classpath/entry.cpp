//
// Created by cyhone on 17-2-22.
//

#include <util/fileutils.h>
#include "classpath/entry.h"
#include "classpath/entry_impls.h"

namespace cyh {

    Entry* newEntry(std::string path) {
        if (StringUtils::exists(path, FileUtils::PATH_LIST_SEPARATOR)) {
            return new CompositeEntry(path);
        }

        if (StringUtils::endsWith(path, "*")) {
            return new WildcardEntry(path);
        }
        if (StringUtils::endsWith(path, ".jar") || StringUtils::endsWith(path, ".JAR")
            || StringUtils::endsWith(path, ".zip") || StringUtils::endsWith(path, ".ZIP")) {
            return new ZipEntry(path);
        }

        return new DirEntry(path);
    }
}

