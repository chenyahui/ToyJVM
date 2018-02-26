//
// Created by cyhone on 18-2-8.
//

#ifndef TOYJVM_EXCEPTION_H
#define TOYJVM_EXCEPTION_H

#include <exception>

namespace jvm {
    class RuntimeException : public std::exception {
    public:
        explicit RuntimeException(const std::string &msg)
                : std::exception(msg)
        {
        }
    };

    class JVMError : public std::exception {
    public:
        explicit JVMError(const std::string &msg)
        {

        }
    };

}
#endif //TOYJVM_EXCEPTION_H
