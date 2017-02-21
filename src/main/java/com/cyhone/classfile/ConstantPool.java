package com.cyhone.classfile;

import java.util.ArrayList;
import java.util.List;

/**
 * @author cyhone
 * @date 2017/2/20
 */
public class ConstantPool {
    List<ConstantInfo> constantInfos = new ArrayList<ConstantInfo>();

    public static ConstantPool readConstantPool(ClassReader classReader) {
        ConstantPool constantPool = new ConstantPool();

        return constantPool;
    }
}
