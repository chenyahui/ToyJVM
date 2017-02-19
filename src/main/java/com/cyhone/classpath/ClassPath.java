package com.cyhone.classpath;

import com.cyhone.exception.EnvCheckError;
import com.cyhone.utils.FilePathUtils;
import com.sun.javafx.scene.shape.PathUtils;
import org.apache.commons.io.FileUtils;
import org.apache.commons.lang3.StringUtils;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;

/**
 * @author cyhone
 * @date 2017/2/14
 */
public class ClassPath {
    private Entry bootClasspath;
    private Entry extClasspath;
    private Entry userClasspath;

    public static Entry newEntry(String path) throws FileNotFoundException {
        if (path.contains(File.pathSeparator)) {
            return new CompositeEntry(path);
        }

        if (path.endsWith("*")) {
            return new WildcardEntry(path);
        }

        if (path.endsWith(".jar") || path.endsWith(".JAR")
                || path.endsWith(".zip") || path.endsWith(".ZIP")) {
            return new ZipJarEntry(path);
        }
        return new DirEntry(path);
    }

    public ClassPath() {
    }

    public ClassPath(String jreOPtion, String cpOption) {
        try {
            parse(jreOPtion, cpOption);
        } catch (FileNotFoundException e) {
            throw new EnvCheckError(e.getMessage());
        }

    }

    public void parse(String jreOPtion, String cpOption) throws FileNotFoundException {
        parseBootAndExtClasspath(jreOPtion);
        parseUserClasspath(cpOption);
    }

    private void parseBootAndExtClasspath(String cpOption) throws FileNotFoundException {
        String jreDir = getJreDir(cpOption);

        //  jre/lib/*
        String jreLibPath = FilePathUtils.join(jreDir, "lib", "*");
        this.bootClasspath = new WildcardEntry(jreLibPath);

        // jre/lib/ext/*
        String jreExtPath = FilePathUtils.join(jreDir, "lib", "ext", "*");
        this.extClasspath = new WildcardEntry(jreExtPath);
    }

    private void parseUserClasspath(String cpOption) throws FileNotFoundException {
        if (StringUtils.isEmpty(cpOption)) {
            cpOption = ".";
        }
        this.userClasspath = newEntry(cpOption);
    }

    private String getJreDir(String cpOption) {
        if (!StringUtils.isEmpty(cpOption) && isExists(cpOption)) {
            return cpOption;
        }

        if (isExists("./jre")) {
            return "./jre";
        }
        String JAVA_HOME = System.getenv("JAVA_HOME");
        if (JAVA_HOME != null) {
            return FilePathUtils.join(JAVA_HOME, "jre");
        }
        throw new EnvCheckError("Can not find jre folder!");
    }

    private boolean isExists(String filepath) {
        return new File(filepath).exists();
    }

    public byte[] readClass(String className) {
        className = className + ".class";
        byte[] classBytes = null;

        try {
            classBytes = bootClasspath.readClass(className);
        } catch (IOException e) {
        }

        try {
            classBytes = extClasspath.readClass(className);
        } catch (IOException e1) {
        }

        try {
            classBytes = userClasspath.readClass(className);
        } catch (IOException e2) {
        }

        return classBytes;
    }
}
