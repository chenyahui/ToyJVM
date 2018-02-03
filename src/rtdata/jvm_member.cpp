#include <glog/logging.h>
#include <jvm/rtdata/access_flag.h>
#include <jvm/rtdata/jvm_member.h>
#include <jvm/rtdata/method_descriptor.h>

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
bool JMember::IsStatic()
{
    return CheckAccess(access_flags_, ACC_FIELD::STATIC);
}

JField::JField(JClass* jclass, MemberInfo* field_info)
    : JMember(jclass, field_info)
{
    auto const_value_attr = field_info->ConstantValueAttribute();
    if (const_value_attr != NULL) {
	const_value_index_ = const_value_attr->constant_value_index();
    }
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
    MethodDescriptorParser parser(descriptor_);
    auto parsed_descriptor = parser.Parse();

    CalcArgsSlotCount(parsed_descriptor.param_types);

    if (IsNative()) {
    }
}
bool JMethod::IsNative()
{
    return CheckAccess(access_flags_, ACC_METHOD::NATIVE);
}
bool JMethod::IsAbstract()
{
    return CheckAccess(access_flags_, ACC_METHOD::ABSTRACT);
}
void JMethod::InjectCodeAttr(std::string& return_type)
{
    max_stack_ = 4;
    max_locals_ = this->args_slot_count_;
    switch (return_type[0]) {
    case 'V': {
	code_ = bytes{ 0xfe, 0xb1 };
	return;
    }
    case 'D': {
	code_ = bytes{ 0xfe, 0xaf };
	return;
    }
    case 'F': {
	code_ = bytes{ 0xfe, 0xae };
	return;
    }
    case 'J': {
	code_ = bytes{ 0xfe, 0xad };
	return;
    }
    case '[':
    case 'L': {
	code_ = bytes{ 0xfe, 0xa0 };
	return;
    }
    default: {
	code_ = bytes{ 0xfe, 0xac };
	return;
    }
    }
}
void JMethod::CalcArgsSlotCount(std::vector<std::string>& param_types)
{
    DLOG(INFO) << "begin parse method descriptor:" << name_;

    for (auto param_type : param_types) {
	DLOG(INFO) << "param_type:" << param_type;
	args_slot_count_++;
	if (param_type == "J" || param_type == "D") {
	    args_slot_count_++;
	}
    }
    if (!IsStatic()) {
	args_slot_count_++;
    }

    DLOG(INFO) << "end parse method descriptor:" << name_ << " args slot count : " << args_slot_count_;
}
