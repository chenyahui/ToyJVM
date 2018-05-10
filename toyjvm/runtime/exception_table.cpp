//
// Created by cyhone on 18-5-10.
//

#include <toyjvm/runtime/exception_table.h>

namespace jvm {
    ExceptionHandler::ExceptionHandler(const jvm::ExceptionInfo &info, jvm::RuntimeConstPool *const_pool)
    {
        start_pc = info.start_pc;
        end_pc = info.end_pc;
        handler_pc = info.handler_pc;
        if (info.catch_type == 0) {
            catch_type = nullptr;
        } else {
            catch_type = const_pool->at<ClassRef *>(info.catch_type);
        }
    }

    ExceptionTable::ExceptionTable(const std::vector<jvm::ExceptionInfo> &infos, jvm::RuntimeConstPool *const_pool)
    {
        exception_handlers_.reserve(infos.size());

        for (auto &info: infos) {
            exception_handlers_.emplace_back(info, const_pool);
        }
    }

    boost::optional<const ExceptionHandler&> ExceptionTable::findExceptionHandler(jvm::JvmClass *ex_class, int pc)
    {
        for (auto &handler : exception_handlers_) {
            if (pc >= handler.start_pc && pc < handler.end_pc) {
                if (handler.catch_type == nullptr) {
                    return handler;
                }

                auto catch_class = handler.catch_type->resolveClass();
                if (catch_class == ex_class || ex_class->isSubClassOf(catch_class)) {
                    return handler;
                }
            }
        }
        return  boost::optional<const ExceptionHandler&>();
    }
}