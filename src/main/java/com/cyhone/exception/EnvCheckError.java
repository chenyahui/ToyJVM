package com.cyhone.exception;

/**
 * @author cyhone
 * @date 2017/2/19
 */
public class EnvCheckError extends Error {
    public EnvCheckError(String message) {
        super(message);
    }

    public EnvCheckError() {
        super();
    }
}
