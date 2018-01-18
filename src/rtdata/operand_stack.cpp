#include <glog/logging.h>
#include <jvm/rtdata/operand_stack.h>
#include <vector>
using namespace cyh;

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
