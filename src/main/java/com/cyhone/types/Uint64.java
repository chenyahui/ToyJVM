package com.cyhone.types;

/**
 * @author cyhone
 * @date 2017/2/20
 */
public class Uint64 {
    byte[] data = new byte[8];

    public Uint64(byte[] data) {
        if (data == null || data.length != 8) {
            throw new IllegalArgumentException("the argument data'length of Uint16's Contruction must be 2");
        }
        this.data = data.clone();
    }
}
