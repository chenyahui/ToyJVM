package com.cyhone.classpath;

import java.io.FileNotFoundException;
import java.io.IOException;

/**
 * @author cyhone
 * @date 2017/2/14
 */
public interface Entry {
    byte[] readClass(String className) throws IOException;
}
