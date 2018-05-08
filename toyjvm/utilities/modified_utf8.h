//
// Created by cyhone on 18-4-14.
//

#ifndef TOYJVM_MODIFY_UTF8_H
#define TOYJVM_MODIFY_UTF8_H

#include <string>
#include <toyjvm/utilities/jvm_types.h>

namespace jvm {
    class UTF16 {
    public:
        explicit UTF16(std::vector<jchar> raw_utf16)
                : raw_utf16_(std::move(raw_utf16))
        {}

        const std::vector<jchar> &rawUTF16() const;

    private:
        std::vector<jchar> raw_utf16_;
    };

    class ModifiedUTF8 {
    public:
        ModifiedUTF8() = default;

        explicit ModifiedUTF8(bytes data)
                : (std::move(data))
        {}

        ModifiedUTF8 &operator=(bytes data);

        bool operator==(const ModifiedUTF8 &other) const;

        bool operator==(const std::string &str) const;

        bool operator==(const bytes &data) const;

        std::vector<jchar> asJCharArr() const;

        std::string asString() const;

        // raw string length
        size_t rawLen() const;

        const bytes &rawUTF8() const;

        // unicode code point count
        size_t unicodeLen() const;

    private:
        std::tuple<jchar, int> next(int start_index) const;

    private:
        bytes raw_utf8_;
    };


    std::string parseMutf8AsString(bytes &data);
}
#endif //TOYJVM_MODIFY_UTF8_H
