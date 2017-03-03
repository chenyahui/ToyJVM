//
// Created by cyhone on 17-3-1.
//

#include <util/byteutils.h>
#include "classfile/classreader.h"


namespace cyh {
    Byte ClassReader::readUint8() {
        auto val = data[0];
        data = Bytes(data.begin() + 1, data.end());
        return val;
    }

    uint16 ClassReader::readUint16() {
        auto val = ByteUtils::twoByteToUint16(data[0], data[1]);
        data = Bytes(data.begin() + 1, data.end());

        return val;
    }

    uint32 ClassReader::readUint32() {
        auto val = ByteUtils::fourByteToUint32(data[0], data[1], data[2], data[3]);
        data = Bytes(data.begin() + 4, data.end());
        return val;
    }

    uint64 ClassReader::readUint64() {
        auto val = ByteUtils::eightByteToUint64(Bytes(data.begin(), data.begin() + 8));

        data = Bytes(data.begin() + 8, data.end());
        return val;
    }

    std::vector<uint16> ClassReader::readUint16s() {

        uint16 n = readUint16();
        std::vector<uint16> results = std::vector<uint16>(n);
        for (uint16 i = 0; i < n; ++i) {
            results[i] = readUint16();
        }
        return results;
    }

    Bytes ClassReader::readBytes(uint32 length) {
        auto val = Bytes(data.begin(), data.begin() + length);
        data = Bytes(data.begin() + length, data.end());
        return val;
    }

}
