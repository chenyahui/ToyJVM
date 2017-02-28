//
// Created by cyh on 17-2-22.
//

#pragma once

#include <string>
#include <cstdlib>
#include <vector>
#include <boost/algorithm/string.hpp>

namespace cyh {

    class StringUtils {

    public:
        static bool exists(std::string str, std::string substr);


        static bool exists(std::string str, char ch);

        static bool endsWith(std::string str, char ch);

        static bool endsWith(std::string str, std::string suffix);

        template<typename T>
        static std::vector<std::string> split(std::string line, T spliter) {
            std::vector<std::string> result;
            return boost::split(result, line, boost::is_any_of(spliter));
        }

    private:
        StringUtils() = delete;
    };
}
