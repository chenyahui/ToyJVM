package com.cyhone.utils;

import org.apache.commons.lang3.ArrayUtils;

import java.nio.Buffer;
import java.nio.ByteBuffer;

/**
 * @author cyhone
 * @date 2017/2/21
 */
public class ByteUtils {
    private ByteUtils() {
    }

    public static short convertBytesToShort(byte[] bytes) {
        return ByteBuffer.wrap(bytes).getShort();
    }

    public static int convertBytesToInt(byte[] bytes) {
        return ByteBuffer.wrap(replenishBytes(bytes, 4)).getInt();
    }

    public static long convertBytesToLong(byte[] bytes) {
        return ByteBuffer.wrap(replenishBytes(bytes, 8)).getLong();
    }

    private static byte[] replenishBytes(byte[] bytes, int targetLen) {
        if (bytes == null || bytes.length > targetLen) {
            throw new IllegalArgumentException("bytes'length must be less than targetLen " + targetLen);
        }
        if (bytes.length == targetLen)
            return bytes;

        byte[] data = new byte[targetLen];
        for (int i = targetLen - bytes.length, j = 0; i < targetLen; i++, j++) {
            data[i] = bytes[j];
        }
        return data;
    }
}
