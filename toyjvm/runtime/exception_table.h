//
// Created by cyhone on 18-5-10.
//

#ifndef TOYJVM_RUNTIME_EXCEPTION_H
#define TOYJVM_RUNTIME_EXCEPTION_H

#include <toyjvm/classfile/attribute_infos.h>
#include <toyjvm/runtime/runtime_const_pool.h>
#include <toyjvm/runtime/symbol_ref.h>
#include <boost/optional.hpp>

namespace jvm {
    struct ExceptionHandler {
        ExceptionHandler(const ExceptionInfo &, RuntimeConstPool *);

        int start_pc;
        int end_pc;
        int handler_pc;
        ClassRef *catch_type;
    };

    class ExceptionTable {
    public:
        ExceptionTable(const std::vector<ExceptionInfo> &exceptions, RuntimeConstPool *);

        boost::optional<const ExceptionHandler &> findExceptionHandler(JvmClass *ex_class, int pc);

    private:
        std::vector<ExceptionHandler> exception_handlers_;
    };

    struct StackTraceElement {
        std::string file_name;
        std::string class_name;
        std::string method_name;
        int line_number;

        inline std::string ToString()
        {
            char buffer[50];
            sprintf(buffer, "%s.%s(%s:%d)", class_name.c_str(), method_name.c_str(), file_name.c_str(), line_number);
            return {buffer};
        }
    };
}
#endif //TOYJVM_EXCEPTION_H
