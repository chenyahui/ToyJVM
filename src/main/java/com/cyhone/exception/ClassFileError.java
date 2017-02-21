package com.cyhone.exception;

/**
 * @author cyhone
 * @date 2017/2/21
 */
public class ClassFileError extends Error {
    public ClassFileError(String message) {
        super(message);
    }

    public ClassFileError() {
        super();
    }
}
