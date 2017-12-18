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
	if (std::is_same<T, double>::value || std::is_same<T, int64_t>::value) {
	    auto vals = ConvertToInt32<T>(data);

	    slots_.push(LocalSlot{.val = vals.first });
	    slots_.push(LocalSlot{.val = vals.second });
	} else if (std::is_same<T, j_ref>::value) {
	    slots_.push(LocalSlot{.ref = data });
	} else if (std::is_same<T, LocalSlot>::value) {
	    slots_.push(data);
	} else {
	    slots_.push(LocalSlot{.val = ConvertToInt32<T>(data) });
	}
    }

    template <typename T>
    T Pop()
    {
	if (std::is_same<T, double>::value || std::is_same<T, int64_t>::value) {
	    auto high = slots_.top().val;
	    slots_.pop();
	    auto low = slots_.top().val;
	    slots_.pop();

	    return ConvertFromInt32<T>(high, low);
	} else if (std::is_same<T, j_ref>::value) {
	    auto ref = slots_.top().ref;
	    slots_.pop();
	    return ref;
	} else if (std::is_same<T, LocalSlot>::value) {
	    auto slot = slots_.top();
	    slots_.pop();
	    return slot;
	} else {
	    auto val = slots_.top().val;
	    slots_.pop();
	    return ConvertFromInt32<T>(val);
	}
    }

private:
    std::stack<LocalSlot> slots_;
};
}
#endif /* ifndef  */
