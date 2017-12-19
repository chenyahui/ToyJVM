#ifndef MY_JVM_RUNTIMEARE_OPERAND_STACK_H
#define MY_JVM_RUNTIMEARE_OPERAND_STACK_H
#include <jvm/rtdata/local_vars.h>
#include <jvm/utils/unsafe.h>
#include <stack>
namespace cyh {
class OperandStack {
public:
    OperandStack() {}

    template <typename T>
    void Push(T data)
    {
	slots_.push(LocalSlot{.val = ConvertToInt32<T>(data) });
    }

    template <typename T>
    T Pop()
    {
	auto val = slots_.top().val;
	slots_.pop();
	return ConvertFromInt32<T>(val);
    }

private:
    std::stack<LocalSlot> slots_;
};
}
#endif /* ifndef  */
