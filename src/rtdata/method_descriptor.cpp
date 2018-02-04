#include <glog/logging.h>
#include <jvm/rtdata/method_descriptor.h>
using namespace cyh;

MethodDescriptor MethodDescriptorParser::Parse()
{
    StartParams();
    ParseParamsType();
    EndParams();
    ParseReturnType();
    Finish();

    return parse_result_;
}

void MethodDescriptorParser::Finish()
{
    if (offset_ != descriptor_.size()) {
	CausePanic();
    }
}
void MethodDescriptorParser::StartParams()
{
    if (ReadChar() != '(') {
	CausePanic();
    }
}
void MethodDescriptorParser::EndParams()
{
    if (ReadChar() != ')') {
	CausePanic();
    }
}
char MethodDescriptorParser::ReadChar()
{
    return descriptor_[offset_++];
}
void MethodDescriptorParser::UnRead()
{
    offset_--;
}
void MethodDescriptorParser::CausePanic()
{
    throw "bad descriptor";
}
std::string MethodDescriptorParser::ParseObjectType()
{
    // to check
    auto arr_start = offset_ - 1;
    auto obj_end = descriptor_.find(';', offset_);
    if (obj_end != std::string::npos) {
	std::string result = descriptor_.substr(arr_start , obj_end - arr_start + 1);
	offset_ = obj_end + 1;
	return result;
    }
    return NULL_TYPE;
}
std::string MethodDescriptorParser::ParseArrayType()
{
    auto arr_start = offset_ - 1;
    ParseFieldType();
    auto arr_end = offset_;
    return descriptor_.substr(arr_start, arr_end - arr_start);
}
std::string MethodDescriptorParser::ParseFieldType()
{
    char c = ReadChar();
    switch (c) {
    case 'B':
    case 'C':
    case 'D':
    case 'F':
    case 'I':
    case 'J':
    case 'S':
    case 'Z':
    case 'V':
	return std::string(1, c);
    case 'L':
	return ParseObjectType();
    case '[':
	return ParseArrayType();
    default:
	UnRead();
	return NULL_TYPE;
    }
}
void MethodDescriptorParser::ParseParamsType()
{
    while (true) {
	std::string param = ParseFieldType();
	if (param == NULL_TYPE) {
	    break;
	}
	parse_result_.param_types.push_back(param);
    }
}
void MethodDescriptorParser::ParseReturnType()
{
    auto return_type = ParseFieldType();

    if (return_type == NULL_TYPE) {
	CausePanic();
    } else {
	parse_result_.return_type = return_type;
    }
}
