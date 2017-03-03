//
// Created by cyhone on 17-3-1.
//

#pragma once

#include <util/byteutils.h>

namespace cyh {
    uint16 ByteUtils::twoByteToUint16(Byte byte1, Byte byte2) {
        return (byte1 << 8) | byte2;
    }

    uint32 ByteUtils::fourByteToUint32(Byte byte1, Byte byte2, Byte byte3, Byte byte4) {
        return byte1 << 24 |
               byte2 << 16 |
               byte3 << 8 |
               byte4;
    }

    uint64 ByteUtils::eightByteToUint64(Bytes bytes) {
        uint64 val = bytes[7];
        for (int i = 8, j = 6; j >= 0; i = i + 8, j--) {
            val |= bytes[j] << i;
        }

        return val;
    }

}
