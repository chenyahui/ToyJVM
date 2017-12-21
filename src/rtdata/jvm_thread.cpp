#include <jvm/rtdata/jvm_thread.h>

namespace cyh {
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
void JThread::NewAndPushFrame(int max_locals, int max_stack)
{
    auto frame = NewFrame(max_locals, max_stack);
    PushFrame(frame);
}
JFrame* JThread::NewFrame(int max_locals, int max_stack)
{
    return new JFrame(this, max_locals, max_stack);
}
}
