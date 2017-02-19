package com.cyhone;

import org.apache.commons.cli.*;

import java.util.Arrays;
import java.util.List;

/**
 * @author cyhone
 * @date 2017/2/14
 */
public class Cmd {
    private Options options;
    private CommandLine cmd;
    private String[] args;

    public Cmd(String[] args) throws ParseException {
        options = new Options();
        init();
        parse(args);
    }

    // java [-options] class [args...]
    void init() {

        // help
        options.addOption("help", false, "help information");
        options.addOption("?", false, "help information");

        //version
        options.addOption("version", false, "print version and exit");

        //classpath
        Option cpOption = Option.builder("classpath")
                .required(false)
                .desc("classpath")
                .hasArg()
                .argName("path")
                .build();
        options.addOption(cpOption);

        Option cpOptionAbbr = Option.builder("cp")
                .required(false)
                .desc("classpath")
                .hasArg()
                .argName("path")
                .build();
        options.addOption(cpOptionAbbr);

        //Xjre
        Option xjreOption = Option.builder("Xjre")
                .required(false)
                .desc("path to jre")
                .hasArg()
                .argName("Xjre")
                .build();
        options.addOption(xjreOption);

    }

    public boolean isHelp() {
        return cmd.hasOption("help") || cmd.hasOption("?");
    }

    public boolean isVersion() {
        return cmd.hasOption("version");
    }

    public void printUsage() {
        HelpFormatter hf = new HelpFormatter();
        String formatstr = "java  [-options] class [args...]";
        hf.printHelp(formatstr, "", this.options, "");
    }

    public String getXjrePath() {
        if (cmd.hasOption("Xjre")) {
            return cmd.getOptionValue("Xjre");
        }
        return "";

    }

    public String getCpPath() {
        if (cmd.hasOption("classpath")) {
            return cmd.getOptionValue("classpath");
        }

        if (cmd.hasOption("cp")) {
            return cmd.getOptionValue("cp");
        }

        return "";
    }

    public String getClassName() {
        return args[0];
    }

    public void printVersion() {
        System.out.println("version 0.0.1");
    }

    public void parse(String[] args) throws ParseException {
        CommandLineParser parser = new DefaultParser();
        cmd = parser.parse(options, args);
        this.args = args.clone();

    }
}
