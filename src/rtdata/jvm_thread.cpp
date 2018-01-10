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

