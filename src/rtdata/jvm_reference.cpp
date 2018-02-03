#include <jvm/rtdata/jvm_class.h>
#include <jvm/rtdata/jvm_member.h>
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

void JObject::SetRefVar(std::string& name, std::string& descriptor, JReference* refer)
{
    auto field = jclass_->GetField(name, descriptor, false);

    fields_->Set<JReference*>(field->slot_index(), refer);
}
JReference* JObject::GetRefVar(std::string& name, std::string& descriptor)
{
    auto field = jclass_->GetField(name, descriptor, false);
    return fields_->Get<JReference*>(field->slot_index());
}
