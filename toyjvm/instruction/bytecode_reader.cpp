//
// Created by cyhone on 18-4-18.
//

#include <toyjvm/instruction/base_instruction.h>

namespace jvm {
    void ByteCodeReader::skipPadding()
    {
        while (pc_ % 4 != 0) {
            BaseReader::read<u1>();
        }
    }
}