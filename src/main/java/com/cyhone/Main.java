package com.cyhone;

import com.cyhone.classpath.ClassPath;
import org.apache.commons.cli.ParseException;
import org.apache.commons.cli.UnrecognizedOptionException;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.Executor;

/**
 * @author cyhone
 * @date 2017/2/14
 */
public class Main {
    public static void main(String[] args) throws ParseException {
        Cmd cmd = null;
        try {
            cmd = new Cmd(args);
        } catch (UnrecognizedOptionException exception) {
            System.err.println(exception.getMessage());
            exitJVM();
        }

        if (cmd.isHelp()) {
            cmd.printUsage();
        } else if (cmd.isVersion()) {
            cmd.printVersion();
        } else {
            startJVM(cmd);
        }
    }

    static void startJVM(Cmd cmd) {
        ClassPath classPath = new ClassPath(cmd.getXjrePath(), cmd.getCpPath());

        byte[] classData = classPath.readClass(cmd.getClassName());

    }

    public static void exitJVM() {
        System.err.println("Error: Could not create the tiny jvm.");
        System.exit(-1);
    }
}
