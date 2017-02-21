package com.cyhone.types;

/**
 * @author cyhone
 * @date 2017/2/20
 */
public class Uint16 {
    byte[] data = new byte[2];
    //0010 1101


    public Uint16(byte[] data) {
        if (data == null || data.length != 2) {
            throw new IllegalArgumentException("the argument data'length of Uint16's Contruction must be 2");
        }
        this.data = data.clone();
    }

    public int toInt() {
        //TODO transfer to int
        int val = ((data[0] & 0xff) << 8) | (data[1] & 0xff);
        return val;
    }

}
