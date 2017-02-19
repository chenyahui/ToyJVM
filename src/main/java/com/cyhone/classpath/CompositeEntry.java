package com.cyhone.classpath;

import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

/**
 * @author cyhone
 * @date 2017/2/14
 */
public class CompositeEntry implements Entry {
    private List<Entry> entrys = new ArrayList<Entry>();

    public CompositeEntry() {

    }

    public CompositeEntry(String pathList) throws FileNotFoundException {
        for (String path : pathList.split("/")) {
            entrys.add(ClassPath.newEntry(path));
        }
    }

    public byte[] readClass(String className) throws FileNotFoundException {
        for (Entry entry : entrys) {
            try {
                return entry.readClass(className);
            } catch (IOException e) {
                continue;
            }
        }

        throw new FileNotFoundException();
    }

    /**
     * 添加
     *
     * @param entry
     */
    public void appendEntry(Entry entry) {
        this.entrys.add(entry);
    }

    @Override
    public String toString() {
        StringBuilder stringBuilder = new StringBuilder();
        for (Entry entry : entrys) {
            stringBuilder.append(entry.toString());
        }
        return stringBuilder.toString();
    }
}
