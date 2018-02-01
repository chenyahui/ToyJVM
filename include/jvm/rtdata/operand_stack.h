#ifndef MY_JVM_RUNTIMEARE_OPERAND_STACK_H
#define MY_JVM_RUNTIMEARE_OPERAND_STACK_H
#include <glog/logging.h>
#include <jvm/rtdata/jvm_reference.h>
#include <jvm/rtdata/local_vars.h>
#include <jvm/utils/unsafe.h>
#include <stack>

// 要添加一个方法，GetRefFromTop，所以这里的底层最好用vector吧
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
	DLOG(INFO) << "opstack push: " << data;
	slots_.push(LocalSlot{.val = ConvertToInt32<T, int>(data) });
    }

    template <typename T>
    T Pop()
    {
	auto val = slots_.top().val;
	slots_.pop();
	return ConvertAtLowLevel<int, T>(val);
    }
    j_ref GetRefFromTop(int n);
    std::stack<LocalSlot> InnerData() { return std::stack<LocalSlot>(slots_); }
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

    DLOG(INFO) << "high: " << high
	       << " low:" << low;
    return Convert2IntToLong(std::make_pair(high, low));
}

template <>
inline j_double OperandStack::Pop<j_double>()
{
    auto l = Pop<j_long>();
    return ConvertAtLowLevel<j_long, j_double>(l);
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

    slots_.push(LocalSlot{.val = vals.first });  // low
    slots_.push(LocalSlot{.val = vals.second }); // high
}
template <>
inline void OperandStack::Push<j_double>(j_double data)
{
    auto vals = ConvertToInt32<j_double, std::pair<int, int> >(data);

    slots_.push(LocalSlot{.val = vals.first });
    slots_.push(LocalSlot{.val = vals.second });
}
template <>
inline void OperandStack::Push<JObject*>(JObject* data)
{
    slots_.push(LocalSlot{.ref = data });
}
template <>
inline void OperandStack::Push<JReference*>(JReference* data)
{
    slots_.push(LocalSlot{.ref = data });
}

template <>
inline j_ref OperandStack::Pop<JReference*>()
{
    auto ref = slots_.top().ref;
    slots_.pop();
    return ref;
}
template <>
inline JObject* OperandStack::Pop<JObject*>()
{
    j_ref data = slots_.top().ref;
    slots_.pop();
    return dynamic_cast<JObject*>(data);
}

template <>
inline void OperandStack::Push<LocalSlot>(LocalSlot slot)
{
    slots_.push(slot);
}
template <>
inline JBaseArray* OperandStack::Pop<JBaseArray*>()
{
    auto data = slots_.top().ref;
    slots_.pop();
    return dynamic_cast<JBaseArray*>(data);
}

template <>
inline void OperandStack::Push<JBaseArray*>(JBaseArray* array_item)
{
    slots_.push(LocalSlot{.ref = array_item });
}
}

#endif /* ifndef  */
