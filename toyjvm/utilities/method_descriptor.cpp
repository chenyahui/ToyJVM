//
// Created by cyhone on 18-5-6.
//
#include <toyjvm/utilities/method_descriptor.h>

namespace jvm {
    MethodDescriptor &MethodDescriptorParser::parse()
    {
        startParams();
        parseParamsType();
        endParams();
        parseReturnType();
        finish();

        return parse_result_;
    }

    void MethodDescriptorParser::finish()
    {
        if (offset_ != descriptor_.size()) {
            causePanic();
        }
    }

    void MethodDescriptorParser::startParams()
    {
        if (readChar() != '(') {
            causePanic();
        }
    }

    void MethodDescriptorParser::endParams()
    {
        if (readChar() != ')') {
            causePanic();
        }
    }

    char MethodDescriptorParser::readChar()
    {
        return descriptor_[offset_++];
    }

    void MethodDescriptorParser::unRead()
    {
        offset_--;
    }

    void MethodDescriptorParser::causePanic()
    {
        throw "bad descriptor";
    }

    std::string MethodDescriptorParser::parseObjectType()
    {
        // to check
        auto arr_start = offset_ - 1;
        auto obj_end = descriptor_.find(';', offset_);
        if (obj_end != std::string::npos) {
            std::string result = descriptor_.substr(arr_start, obj_end - arr_start + 1);
            offset_ = obj_end + 1;
            return result;
        }
        return NULL_TYPE;
    }

    std::string MethodDescriptorParser::parseArrayType()
    {
        auto arr_start = offset_ - 1;
        parseFieldType();
        auto arr_end = offset_;
        return descriptor_.substr(arr_start, arr_end - arr_start);
    }

    std::string MethodDescriptorParser::parseFieldType()
    {
        char c = readChar();
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
                return parseObjectType();
            case '[':
                return parseArrayType();
            default:
                unRead();
                return NULL_TYPE;
        }
    }

    void MethodDescriptorParser::parseParamsType()
    {
        while (true) {
            std::string param = parseFieldType();
            if (param == NULL_TYPE) {
                break;
            }
            parse_result_.param_types.push_back(param);
        }
    }

    void MethodDescriptorParser::parseReturnType()
    {
        auto return_type = parseFieldType();

        if (return_type == NULL_TYPE) {
            causePanic();
        } else {
            parse_result_.return_type = return_type;
        }
    }
}
