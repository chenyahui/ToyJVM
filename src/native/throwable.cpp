#include <jvm/native/throwable.h>
#include <jvm/rtdata/jvm_frame.h>
#include <jvm/rtdata/jvm_reference.h>
#include <jvm/rtdata/jvm_thread.h>
#include <glog/logging.h>

namespace cyh {
std::vector<StackTraceElement>* CreateStackTraceElements(JObject* tobj, JThread* jthread);
StackTraceElement CreateStackTraceElement(JFrame* frame);
int DistanceToObject(JClass*);

std::string StackTraceElement::ToString()
{
    char buffer[50];
    sprintf(buffer, "%s.%s(%s:%d)", class_name.c_str(), method_name.c_str(), file_name.c_str(), line_number);
    return { buffer };
}
void fillInStackTrace(JFrame* frame)
{
    DLOG(INFO) << "fillInStackTrace come in ++++++++++++++++++++++++";
    auto this_obj = frame->LocalVars().GetThis();
    frame->OpStack().Push<JObject*>(this_obj);
    auto stack_traces = CreateStackTraceElements(this_obj, frame->Thread());
    this_obj->set_extra((char*)stack_traces);
}

std::vector<StackTraceElement>* CreateStackTraceElements(JObject* tobj, JThread* jthread)
{
    auto skip = DistanceToObject(tobj->jclass()) + 2;
    auto frame_vec = jthread->GetFrames();

    std::vector<JFrame*> frames(frame_vec.begin() + skip, frame_vec.end());
    auto result = new std::vector<StackTraceElement>();

    for (auto frame : frames) {
	result->push_back(CreateStackTraceElement(frame));
    }

    return result;
}
StackTraceElement CreateStackTraceElement(JFrame* frame)
{
    auto method = frame->jmethod();
    auto jclass = method->jclass();

    return {
	jclass->source_file(),
	jclass->JavaName(),
	method->name(),
	method->GetLineNumber(frame->NextPc() - 1)
    };
}
int DistanceToObject(JClass* jclass)
{
    int distance = 0;
    for (auto c = jclass->super_class(); c != NULL; c = c->super_class()) {
	distance++;
    }
    return distance;
}
}
