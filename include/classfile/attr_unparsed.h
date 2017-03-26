#include "attributeinfo.h"

namespace cyh {
    class UnparsedAttribute : public AttributeInfo {
    private:
        std::string name;
        uint32 length;
        Bytes info;
    public:
        UnparsedAttribute(std::string name, uint32 length, Bytes info);

        void readInfo(ClassReader reader) override;

        Bytes Info();
    };
}
