#pragma once

#include <types.h>

namespace cyh {
    class ByteUtils {
    public:
        static uint16 twoByteToUint16(Byte byte1, Byte byte2);

        static uint32 fourByteToUint32(Byte byte1, Byte byte2, Byte byte3, Byte byte4);

        static uint64 eightByteToUint64(Bytes bytes);
    };
}