//
// Created by cyhone on 18-4-15.
//

#ifndef TOYJVM_BYTECODE_READER_H
#define TOYJVM_BYTECODE_READER_H

#include <toyjvm/utilities/basereader.h>

namespace jvm {
    class ByteCodeReader : public BaseReader {
    public:
        explicit ByteCodeReader(bytes &data)
                : BaseReader(data)
        {}

        ByteCodeReader(const ByteCodeReader &reader)
                : BaseReader(reader)
        {}

        void skipPadding();
    };
}
#endif //TOYJVM_BYTECODE_READER_H
