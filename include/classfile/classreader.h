#pragma once

#include <types.h>

namespace cyh {
    class ClassReader {
    public:
        Byte readUint8();

        uint16 readUint16();

        uint32 readUint32();

        uint64 readUint64();

        std::vector<uint16> readUint16s();

        Bytes readBytes(uint32 length);

    private:
        Bytes data;
    };

}