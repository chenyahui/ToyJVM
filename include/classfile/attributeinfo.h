#pragma once


namespace cyh {
    using AttributeInfos = std::vector<AttributeInfo>;

    class AttributeInfo {

    };

    AttributeInfos readAttributes(ClassReader reader, ConstantPool cp);
}
