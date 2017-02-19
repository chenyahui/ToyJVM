package com.cyhone.classpath;

import org.apache.commons.io.IOUtils;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.zip.ZipEntry;
import java.util.zip.ZipFile;

/**
 * @author cyhone
 * @date 2017/2/14
 */
public class ZipJarEntry implements Entry {
    private String absoluteDir = null;

    public ZipJarEntry(File file) {
        absoluteDir = file.getAbsolutePath();
    }

    public ZipJarEntry(String path) {
        File pathFile = new File(path);
        absoluteDir = pathFile.getAbsolutePath();
    }

    @Override
    public String toString() {
        return absoluteDir;
    }

    public byte[] readClass(String className) throws IOException {
        ZipFile zip = new ZipFile(absoluteDir);
        ZipEntry classEntry = zip.getEntry(className);
        if (classEntry == null) {
            throw new FileNotFoundException();
        }
        return IOUtils.toByteArray(zip.getInputStream(classEntry));
    }
}
