//
// Created by cyhone on 18-4-15.
//

#include <toyjvm/common/basereader.h>

namespace jvm {

    template<>
    float BaseReader::read<float>()
    {
        auto raw_bits = read<int>();
        return bits_cast<int, float>(raw_bits);
    };

    template<>
    double BaseReader::read<double>()
    {
        auto raw_bits = read<long>();
        return bits_cast<long, double>(raw_bits);
    };
}