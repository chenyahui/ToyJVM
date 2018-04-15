//
// Created by cyhone on 18-2-8.
//

#ifndef TOYJVM_EXCEPTION_H
#define TOYJVM_EXCEPTION_H

#include <exception>
#include <string>
#include <stdexcept>

namespace jvm {
    class RuntimeException : public std::logic_error {
    public:
        explicit RuntimeException(const std::string& msg)
                : std::logic_error(msg)
        {}

    };

    class JVMError : public std::runtime_error {
    public:
        explicit JVMError(const std::string &msg)
                : std::runtime_error(msg)
        {
        }
    };

    class ClassFormatError : public JVMError {
    public:
        explicit ClassFormatError(const std::string &msg)
                : JVMError("class file format error: " + msg)
        {

        }
    };

    class ClassNotFound : public JVMError {
    public:
        explicit ClassNotFound(const std::string &class_name)
                : JVMError("class not found: " + class_name)
        {
        }
    };

}
#endif //TOYJVM_EXCEPTION_H
