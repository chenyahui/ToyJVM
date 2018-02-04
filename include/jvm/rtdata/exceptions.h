#ifndef TOYJVM_RTDATA_EXCEPTIONS_H
#define TOYJVM_RTDATA_EXCEPTIONS_H
#include <jvm/classfile/attribute_infos.h>

#include <vector>
namespace cyh {

class ClassRef;
class RuntimeConstPool;
class JClass;
struct ExceptionHandler {
    ExceptionHandler(ExceptionInfo&, RuntimeConstPool*);
    int start_pc;
    int end_pc;
    int handler_pc;
    ClassRef* catch_type;
};

class ExceptionTable {
public:
    ExceptionTable(std::vector<ExceptionInfo>& exceptions, RuntimeConstPool*);

    ExceptionHandler* FindExceptionHandler(JClass* ex_class, int pc);

private:
    std::vector<ExceptionHandler*> exception_handlers_;
};
};

#endif /* end of include guard: TOYJVM_EXCEPTIONS_H */
