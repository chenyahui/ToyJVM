#include <jvm/rtdata/access_flag.h>
#include <jvm/rtdata/jvm_member.h>

using namespace cyh;

JMember::JMember(JClass* jclass, MemberInfo* member_info)
    : jclass_(jclass)
{
    access_flags_ = member_info->access_flags();
    name_ = member_info->MemberName();
    descriptor_ = member_info->Descriptor();
}

bool JMember::IsAccessibleTo(JClass* d)
{
    auto c = this->jclass_;
    if (IsPublic() || d == c) {
	return true;
    }
    if (IsProtected()) {
	return d->IsSubClassOf(c)
	    || d->GetPackageName() == c->GetPackageName();
    }

    if (!IsPrivate()) {
	return c->GetPackageName() == c->GetPackageName();
    }

    return false;
}

bool JMember::IsPublic()
{
    return CheckIsPublic(access_flags_);
}

bool JMember::IsPrivate()
{
    return CheckAccess(access_flags_, ACC_FIELD::PRIVATE);
}
bool JMember::IsProtected()
{
    return CheckAccess(access_flags_, ACC_FIELD::PROTECTED);
}
JField::JField(JClass* jclass, MemberInfo* field_info)
    : JMember(jclass, field_info)
{
    auto const_value_attr = field_info->ConstantValueAttribute();
    if (const_value_attr != NULL) {
	const_value_index_ = const_value_attr->constant_value_index();
    }
}

bool JField::IsStatic()
{
    return CheckAccess(access_flags_, ACC_FIELD::STATIC);
}

bool JField::IsLongOrDouble()
{
    return descriptor_ == "J" || descriptor_ == "D";
}

bool JField::IsFinal()
{
    return CheckAccess(access_flags_, ACC_FIELD::FINAL);
}
JMethod::JMethod(JClass* jclass, MemberInfo* method_info)
    : JMember(jclass, method_info)
{
    code_attr_ = method_info->CodeAttribute();
    if (code_attr_ != NULL) {
	max_stack_ = code_attr_->max_stack_;
	max_locals_ = code_attr_->max_locals_;
	code_ = code_attr_->code_;
    }
}
