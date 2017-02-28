//
// Created by cyhone on 17-2-26.
//

#pragma once

#include <string>
#include <iostream>

namespace cyh {
    std::string getEnv(std::string key);

    void error(std::string msg);
    void errorAndExist(std::string msg);
    template<typename T>
    void print(T t) {
        std::cout << t;
    }

    template<typename T, typename ...U>
    void print(T t, U ...u) {
        std::cout << t;
        print(u...);
    }


    template<typename ...U>
    void println(U ...u) {

        print(u...);
        std::cout << std::endl;
    }
}

