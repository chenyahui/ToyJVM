#ifndef MY_JVM_RUNTIMEARE_OPERAND_STACK_H
#define MY_JVM_RUNTIMEARE_OPERAND_STACK_H
#include <jvm/rtdata/local_vars.h>
#include <jvm/utils/unsafe.h>
#include <stack>
namespace cyh {
class OperandStack {
public:
    OperandStack(int max_stack)
	: max_stack_(max_stack)
    {
    }

    template <typename T>
    void Push(T data)
    {
	slots_.push(LocalSlot{.val = ConvertToInt32<T, int>(data) });
    }

    template <typename T>
    T Pop()
    {
	auto val = slots_.top().val;
	slots_.pop();
	return ConvertFromInt32<int, T>(val, 0);
    }

private:
    std::stack<LocalSlot> slots_;
    int max_stack_;
};
}
namespace cyh {
template <>
inline j_long OperandStack::Pop<j_long>()
{
    auto high = slots_.top().val;
    slots_.pop();
    auto low = slots_.top().val;
    slots_.pop();

    return Convert2IntToLong(std::make_pair(high, low));
}

template <>
inline j_double OperandStack::Pop<j_double>()
{
    auto l = Pop<j_long>();
    return ConvertAtLowLevel<j_long, j_double>(l);
}
template <>
inline j_ref OperandStack::Pop<j_ref>()
{
    auto ref = slots_.top().ref;
    slots_.pop();
    return ref;
}
template <>
inline LocalSlot OperandStack::Pop<LocalSlot>()
{
    auto slot = slots_.top();
    slots_.pop();
    return slot;
}

template <>
inline void OperandStack::Push<j_long>(j_long data)
{
    auto vals = ConvertToInt32<j_long, std::pair<int, int> >(data);

    slots_.push(LocalSlot{.val = vals.first });
    slots_.push(LocalSlot{.val = vals.second });
}
template <>
inline void OperandStack::Push<j_double>(j_double data)
{
    auto vals = ConvertToInt32<j_double, std::pair<int, int> >(data);

    slots_.push(LocalSlot{.val = vals.first });
    slots_.push(LocalSlot{.val = vals.second });
}
template <>
inline void OperandStack::Push<j_ref>(j_ref data)
{
    slots_.push(LocalSlot{.ref = data });
}
template <>
inline void OperandStack::Push<LocalSlot>(LocalSlot slot)
{
    slots_.push(slot);
}
}

#endif /* ifndef  */
