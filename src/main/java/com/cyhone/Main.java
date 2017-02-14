package com.cyhone;

import org.apache.commons.cli.ParseException;
import org.apache.commons.cli.UnrecognizedOptionException;

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
            
        }
    }

    void startJVM(Cmd cmd) {

    }

    public static void exitJVM() {
        System.err.println("Error: Could not create the tiny jvm.");
        System.exit(-1);
    }
}
