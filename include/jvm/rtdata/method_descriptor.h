#ifndef TOYJVM_RTDATA_METHOD_DESCRIPTOR_H
#define TOYJVM_RTDATA_METHOD_DESCRIPTOR_H

#include <string>
#include <vector>

namespace cyh {

struct MethodDescriptor {
    std::vector<std::string> param_types;
    std::string return_type;
};

class MethodDescriptorParser {
public:
    MethodDescriptorParser(std::string descriptor)
	: descriptor_(descriptor)
	, offset_(0)
    {
    }
    MethodDescriptor Parse();

private:
    void Finish();
    void StartParams();
    void EndParams();
    char ReadChar();
    void UnRead();
    void CausePanic();
    std::string ParseObjectType();
    std::string ParseArrayType();
    std::string ParseFieldType();
    void ParseParamsType();
    void ParseReturnType();

private:
    MethodDescriptor parse_result_;
    std::string descriptor_;
    int offset_;
    const std::string NULL_TYPE = "NULL";
};
}

#endif /* end of include guard: TOYJVM_RTDATA_DESCRIPTOR_H */
