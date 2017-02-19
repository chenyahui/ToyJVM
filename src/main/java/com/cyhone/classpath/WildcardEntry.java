package com.cyhone.classpath;

import java.io.File;
import java.io.FileNotFoundException;

/**
 * @author cyhone
 * @date 2017/2/14
 */
public class WildcardEntry implements Entry {
    CompositeEntry compositeEntry;

    public WildcardEntry(String path) throws FileNotFoundException {
        File baseDir = new File(path.substring(0, path.length() - 1));
        if (!(baseDir.exists() && baseDir.isDirectory())) {
            throw new FileNotFoundException();
        }
        compositeEntry = new CompositeEntry();
        walkPath(baseDir);
    }

    private void walkPath(File baseDir) {
        for (File file : baseDir.listFiles()) {
            if (file.isFile()) {
                String filename = file.getPath();
                if (filename.endsWith(".jar") || filename.endsWith(".JAR")) {
                    this.compositeEntry.appendEntry(new ZipJarEntry(file));
                }
            }
        }
    }

    public byte[] readClass(String className) throws FileNotFoundException {
        return this.compositeEntry.readClass(className);
    }
}
