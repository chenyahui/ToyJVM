package com.cyhone.classfile;


import com.cyhone.utils.ByteUtils;
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

    public char readChar() {
        char val = (char) data[0];
        data = sliceData(1);
        return val;
    }

    public short readShort() {
        short val = ByteUtils.convertBytesToShort(sliceData(0, 2));
        data = sliceData(2);
        return val;
    }

    public int readInt() {
        int val = ByteUtils.convertBytesToInt(sliceData(0, 4));
        data = sliceData(4);
        return val;
    }

    public long readLong() {
        long val = ByteUtils.convertBytesToLong(sliceData(0, 8));
        data = sliceData(8);
        return val;
    }

    public short[] readShorts() {
        short n = readShort();
        short[] result = new short[n];

        for (int i = 0; i < n; i++) {
            result[i] = readShort();
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
