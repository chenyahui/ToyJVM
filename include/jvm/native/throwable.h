#ifndef TOYJVM_NATIVE_THROWABLE_H
#define TOYJVM_NATIVE_THROWABLE_H
#include <string>

namespace cyh {
class JFrame;
struct StackTraceElement {
    std::string file_name;
    std::string class_name;
    std::string method_name;
    int line_number;

    std::string ToString();
};
void fillInStackTrace(JFrame* frame);
}

#endif /* end of include guard: TOYJVM_NATIVE_THROWABLE_H */
