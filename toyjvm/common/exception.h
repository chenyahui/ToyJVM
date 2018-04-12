//
// Created by cyhone on 18-2-8.
//

#ifndef TOYJVM_EXCEPTION_H
#define TOYJVM_EXCEPTION_H

#include <exception>
#include <string>

namespace jvm {
    class RuntimeException : public std::runtime_error {
    public:
        explicit RuntimeException(const std::string &msg)
                : std::runtime_error(msg) {
        }
    };

    class JVMError : public std::runtime_error {
    public:
        explicit JVMError(const std::string &msg)
                : std::runtime_error(msg) {
        }
    };

    class ClassNotFound : public JVMError {
    public:
        ClassNotFound()
                : JVMError("class not found") {
        }
    };

}
#endif //TOYJVM_EXCEPTION_H
