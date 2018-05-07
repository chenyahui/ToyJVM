//
// Created by cyhone on 18-4-14.
//

#ifndef TOYJVM_MODIFY_UTF8_H
#define TOYJVM_MODIFY_UTF8_H

#include <string>
#include <toyjvm/utilities/jvm_types.h>

namespace jvm {
    class Utf16;

    class ModifiedUTF8 {
    public:
        explicit ModifiedUTF8(bytes data)
                : raw_utf8_(std::move(data))
        {}

        bool operator==(const ModifiedUTF8 &other) const;

        bool operator==(const std::string &str) const;

        bool operator==(const bytes &data) const;

        Utf16 asUTF16() const;

        // raw string length
        size_t rawLen() const;

        // unicode code point count
        size_t unicodeLen() const;

    private:

        std::tuple<jchar, int> next(int start_index) const;

    private:
        bytes raw_utf8_;
    };

    class UTF16 {
    public:
        explicit UTF16(std::vector<jchar> raw_utf16)
                : raw_utf16_(std::move(raw_utf16))
        {}

    private:
        std::vector<jchar> raw_utf16_;
    };

    std::string parseMutf8AsString(bytes &data);
}
#endif //TOYJVM_MODIFY_UTF8_H
