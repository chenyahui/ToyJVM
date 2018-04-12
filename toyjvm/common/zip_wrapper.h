//
// Created by cyhone on 2018/3/8.
//

#ifndef TOYJVM_ZIP_WRAPPER_H
#define TOYJVM_ZIP_WRAPPER_H

#include <boost/core/noncopyable.hpp>
#include <string>
#include <zip.h>
#include "jvm_types.h"

namespace jvm {
    class ZipAchive : boost::noncopyable {
    public:
        ZipAchive(const std::string &zip_file) {
            int err;
            if ((zipFile_ = zip_open(zip_file.c_str(), 0, &err)) == NULL) {

            }
        }

        jvm::bytes readFile(const std::string &filename) {
            return jvm::bytes();
        }

        bool exists(const std::string &filename) {
            return false;
        }

        ~ZipAchive() {
            zip_close(zipFile_);
        }

    private:
        zip *zipFile_;
    };
}
#endif //TOYJVM_ZIP_WRAPPER_H
