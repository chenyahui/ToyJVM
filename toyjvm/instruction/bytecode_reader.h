//
// Created by cyhone on 18-4-15.
//

#ifndef TOYJVM_BYTECODE_READER_H
#define TOYJVM_BYTECODE_READER_H

#include <toyjvm/utilities/bytereader.h>

namespace jvm {
    class ByteCodeReader : public ByteReader {
    public:
        explicit ByteCodeReader(bytes &data)
                : ByteReader(data)
        {}

        void skipPadding();
    };
}
#endif //TOYJVM_BYTECODE_READER_H
