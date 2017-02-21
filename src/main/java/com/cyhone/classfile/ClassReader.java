package com.cyhone.classfile;

import com.cyhone.types.Uint16;
import com.cyhone.types.Uint32;
import com.cyhone.types.Uint64;
import com.cyhone.types.Uint8;
import org.apache.commons.lang3.ArrayUtils;

/**
 * @author cyhone
 * @date 2017/2/20
 */
public class ClassReader {
    byte[] data;

    public ClassReader(byte[] data) {
        this.data = data.clone();
    }

    public Uint8 readUint8() {
        Uint8 val = new Uint8(data[0]);
        data = sliceData(1);
        return val;
    }

    public Uint16 readUint16() {
        Uint16 val = new Uint16(sliceData(0, 2));
        data = sliceData(2);
        return val;
    }

    public Uint32 readUint32() {
        Uint32 val = new Uint32(sliceData(0, 4));
        data = sliceData(4);
        return val;
    }

    public Uint64 readUint64() {
        Uint64 val = new Uint64(sliceData(0, 8));
        data = sliceData(8);
        return val;
    }

    public Uint16[] readUint16s() {
        int n = readUint16().toInt();
        Uint16[] result = new Uint16[n];

        for (int i = 0; i < n; i++) {
            result[i] = readUint16();
        }

        return result;
    }

    public byte[] readBytes(int n) {
        byte[] val = sliceData(0, n);
        data = sliceData(n);
        return val;
    }

    private byte[] sliceData(int start) {
        return sliceData(start, data.length);
    }

    private byte[] sliceData(int start, int end) {
        return ArrayUtils.subarray(data, start, end);
    }
}
