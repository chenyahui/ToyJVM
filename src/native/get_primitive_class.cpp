#include <jvm/native/get_primitive_class.h>
#include <jvm/rtdata/class_loader.h>
#include <jvm/rtdata/jvm_frame.h>
#include <jvm/rtdata/string_pool.h>

namespace cyh {

void getPrimitiveClass(JFrame* frame)
{
    auto name_obj = frame->LocalVars().Get<JObject*>(0);
    auto name = TransJString(name_obj);
    auto loader = name_obj->jclass()->class_loader();
    auto jlc_obj = loader->LoadClass(name)->jl_class();

    frame->OpStack().Push<JObject*>(jlc_obj);
}
}
