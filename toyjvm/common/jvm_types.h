//
// Created by cyhone on 18-2-8.
//

#ifndef TOYJVM_TYPES_H
#define TOYJVM_TYPES_H

#include <cstdint>
#include <vector>

namespace jvm{
    using u8 = uint64_t;
    using u4 = uint32_t;
    using u2 = uint16_t;
    using u1 = uint8_t;
    using bytes = std::vector<u1>;


}
#endif //TOYJVM_TYPES_H
