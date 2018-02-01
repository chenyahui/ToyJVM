#include <jvm/rtdata/jvm_class.h>
#include <jvm/rtdata/jvm_reference.h>

using namespace cyh;

JObject::JObject(JClass* jclass)
    : JReference(jclass)
{
    fields_ = new LocalVarRefs(jclass->instance_slot_count());
}
bool JObject::IsInstanceOf(JClass* jclass)
{
    return jclass->IsAssignableFrom(this->jclass_);
}
