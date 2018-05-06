//
// Created by cyhone on 18-5-6.
//

#ifndef TOYJVM_METHOD_DESCRIPTOR_H
#define TOYJVM_METHOD_DESCRIPTOR_H

#include <string>
#include <vector>

namespace jvm {
    struct MethodDescriptor {
        std::vector<std::string> param_types;
        std::string return_type;
    };

    class MethodDescriptorParser {
    public:
        explicit MethodDescriptorParser(const std::string &descriptor)
                : descriptor_(descriptor), offset_(0)
        {}

        MethodDescriptor &parse();

    private:
        void finish();

        void startParams();

        void endParams();

        char readChar();

        void unRead();

        void causePanic();

        std::string parseObjectType();

        std::string parseArrayType();

        std::string parseFieldType();

        void parseParamsType();

        void parseReturnType();

    private:
        MethodDescriptor parse_result_;
        std::string descriptor_;
        int offset_;
        const std::string NULL_TYPE = "NULL";
    };

    MethodDescriptor parseMethodDescriptor(const std::string &descriptor)
    {
        MethodDescriptorParser methodDescriptorParser(descriptor);
        return methodDescriptorParser.parse();
    }
}

#endif //TOYJVM_METHOD_DESCRIPTOR_H
