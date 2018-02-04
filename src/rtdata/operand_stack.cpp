#include <glog/logging.h>
#include <jvm/rtdata/operand_stack.h>
#include <vector>
using namespace cyh;

void OperandStack::Clear()
{
    // 这里应该对localslot的ref做一个delete，但是localslot是一个union。。。是不是改成struct才行呢。。
    // 这里暂时内存泄露吧

    while (!slots_.empty()) {
	slots_.pop();
    }
}
j_ref OperandStack::GetRefFromTop(int n)
{
    DLOG(INFO) << "get ref from top : " << n;
    std::vector<LocalSlot> temp;

    for (int i = 0; i < n; ++i) {
	temp.push_back(slots_.top());
	slots_.pop();
    }
    assert(slots_.size() > 0);
    auto result = slots_.top().ref;

    for (int i = temp.size(); i > 0; --i) {
	slots_.push(temp[i - 1]);
    }

    return result;
}
