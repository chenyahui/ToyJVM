package com.cyhone.utils;

import java.io.File;

/**
 * @author cyhone
 * @date 2017/2/19
 */
public class FilePathUtils {
    private FilePathUtils() {

    }

    public static String join(String... fileItems) {
        StringBuilder path = new StringBuilder();
        for (String item : fileItems) {
            path.append(item);
            if (!item.endsWith(File.pathSeparator)) {
                path.append(File.pathSeparator);
            }
        }

        return path.substring(0, path.length() - 1); //remove the last path separator
    }
}
