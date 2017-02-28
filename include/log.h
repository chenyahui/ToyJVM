//
// Created by cyhone on 17-2-26.
//
#pragma once

#include <iostream>

namespace cyh {
    class Log {
    public:
        template<typename T>
        static void d(T msg) {
            if (nowLevel <= LOG_LEVEL::DEBUG) {
                std::cout << msg << std::endl;
            }
        }

        template<typename T>
        static void i(T msg) {
            if (nowLevel <= LOG_LEVEL::INFO) {
                std::cout << msg << std::endl;
            }
        }

        template<typename T>
        static void w(T msg) {
            if (nowLevel <= LOG_LEVEL::WARN) {
                std::cout << msg << std::endl;
            }
        }

        template<typename T>
        static void e(T msg) {
            if (nowLevel <= LOG_LEVEL::ERROR) {
                std::cerr << msg << std::endl;
            }
        }

        template<typename T>
        static void f(T msg) {
            if (nowLevel <= LOG_LEVEL::FATAL) {
                std::cerr << msg << std::endl;
                std::terminate();
            }
        }

        enum LOG_LEVEL {
            ALL,
            DEBUG,
            INFO,
            WARN,
            ERROR,
            FATAL,
            OFF
        };
    private:
        static const LOG_LEVEL nowLevel;

    };
}