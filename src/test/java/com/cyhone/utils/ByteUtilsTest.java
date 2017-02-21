package com.cyhone.utils;

import junit.framework.TestCase;
import org.junit.Test;

import static org.junit.Assert.*;

/**
 * @author cyhone
 * @date 2017/2/21
 */
public class ByteUtilsTest {
    @Test
    public void convertBytesToShort() throws Exception {
        assertEquals(ByteUtils.convertBytesToShort(new byte[]{0, 1}), 1);
        assertEquals(ByteUtils.convertBytesToShort(new byte[]{1, 1}), 257);
    }

    @Test
    public void convertBytesToInt() throws Exception {
        assertEquals(ByteUtils.convertBytesToInt(new byte[]{0, 0, 0, 1}), 1);
        assertEquals(ByteUtils.convertBytesToInt(new byte[]{0, 1}), 1);
        assertEquals(ByteUtils.convertBytesToInt(new byte[]{0, 0, 1, 1}), 257);
        assertEquals(ByteUtils.convertBytesToInt(new byte[]{0, 1, 1}), 257);
        assertEquals(ByteUtils.convertBytesToInt(new byte[]{1, 1}), 257);
    }

    @Test
    public void convertBytesToLong() throws Exception {
        assertEquals(ByteUtils.convertBytesToLong(new byte[]{0, 0, 0, 1}), 1);
        assertEquals(ByteUtils.convertBytesToLong(new byte[]{0, 1}), 1);
        assertEquals(ByteUtils.convertBytesToLong(new byte[]{0, 0, 1, 1}), 257);
        assertEquals(ByteUtils.convertBytesToLong(new byte[]{0, 1, 1}), 257);
        assertEquals(ByteUtils.convertBytesToLong(new byte[]{1, 1}), 257);
    }

}