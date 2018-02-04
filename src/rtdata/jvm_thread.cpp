#include <jvm/rtdata/jvm_thread.h>
using namespace cyh;

JFrame* JThread::PopFrame()
{
    auto frame = stack_.top();
    stack_.pop();
    return frame;
}
void JThread::PushFrame(JFrame* frame)
{
    stack_.push(frame);
}
JFrame* JThread::TopFrame()
{
    return stack_.top();
}

void JThread::ClearStack()
{
    while (!stack_.empty()) {
	stack_.pop();
    }
}

std::vector<JFrame*> JThread::GetFrames()
{
    std::vector<JFrame*> result;
    while (!stack_.empty()) {
	result.push_back(stack_.top());
	stack_.pop();
    }

    for (int i = result.size() - 1; i >= 0; i--) {
	stack_.push(result[i]);
    }
    return result;
}
