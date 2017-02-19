package com.cyhone.classpath;

import org.apache.commons.io.FileUtils;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;

/**
 * @author cyhone
 * @date 2017/2/14
 */
public class DirEntry implements Entry {
    private String absoluteDir = null;

    public DirEntry(String path) {
        File pathFile = new File(path);

        absoluteDir = pathFile.getAbsolutePath();
    }

    public byte[] readClass(String className) throws IOException {
        String classPath = absoluteDir + File.pathSeparator + className;
        return FileUtils.readFileToByteArray(new File(classPath));
    }

    @Override
    public String toString() {
        return absoluteDir;
    }
}
