#include <jvm/rtdata/operand_stack.h>

namespace cyh {
template <>
j_long OperandStack::Pop<j_long>()
{
    auto high = slots_.top().val;
    slots_.pop();
    auto low = slots_.top().val;
    slots_.pop();

    return ConvertFromInt32<std::pair<int, int>, j_long>(std::make_pair(high, low), 0);
}

template <>
j_double OperandStack::Pop<j_double>()
{
    auto l = Pop<j_long>();
    return ConvertAtLowLevel<j_long, j_double>(l);
}
template <>
j_ref OperandStack::Pop<j_ref>()
{
    auto ref = slots_.top().ref;
    slots_.pop();
    return ref;
}
template <>
LocalSlot OperandStack::Pop<LocalSlot>()
{
    auto slot = slots_.top();
    slots_.pop();
    return slot;
}

template <>
void OperandStack::Push<j_long>(j_long data)
{
    auto vals = ConvertToInt32<j_long, std::pair<int, int> >(data);

    slots_.push(LocalSlot{.val = vals.first });
    slots_.push(LocalSlot{.val = vals.second });
}
template <>
void OperandStack::Push<j_double>(j_double data)
{
    auto vals = ConvertToInt32<j_double, std::pair<int, int> >(data);

    slots_.push(LocalSlot{.val = vals.first });
    slots_.push(LocalSlot{.val = vals.second });
}
template <>
void OperandStack::Push<j_ref>(j_ref data)
{
    slots_.push(LocalSlot{.ref = data });
}
template <>
void OperandStack::Push<LocalSlot>(LocalSlot slot)
{
    slots_.push(slot);
}
}
