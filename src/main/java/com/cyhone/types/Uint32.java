package com.cyhone.types;

/**
 * @author cyhone
 * @date 2017/2/20
 */
public class Uint32 {
    byte[] data = new byte[4];

    public Uint32(byte[] data) {
        if (data == null || data.length != 4) {
            throw new IllegalArgumentException("the argument data'length of Uint16's Contruction must be 2");
        }
        this.data = data.clone();
    }

    public int toInt() {
        return 0;
    }
}
