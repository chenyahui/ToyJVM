//
// Created by cyhone on 18-2-10.
//

#ifndef TOYJVM_STRUTILS_H
#define TOYJVM_STRUTILS_H

#include <string>
#include <sstream>
#include <vector>

namespace jvm {
    template<typename Out>
    void split(const std::string &s, char delim, Out result)
    {
        std::stringstream ss(s);
        std::string item;
        while (std::getline(ss, item, delim)) {
            *(result++) = item;
        }
    }

    inline std::vector<std::string> split(const std::string &s, char delim)
    {
        std::vector<std::string> elems;
        split(s, delim, std::back_inserter(elems));
        return elems;
    }

    template<class S, class T>
    std::string join(std::vector<T> &elems, S &delim)
    {
        std::stringstream ss;
        typename std::vector<T>::iterator e = elems.begin();
        ss << *e++;
        for (; e != elems.end(); ++e) {
            ss << delim << *e;
        }
        return ss.str();
    }

    inline bool ends_with(std::string const &value, std::string const &ending)
    {
        if (ending.size() > value.size())
            return false;
        return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
    }

    inline bool starts_with(std::string const &value, std::string const &starting)
    {
        if (starting.size() > value.size())
            return false;
        return std::equal(starting.begin(), starting.end(), value.begin());
    }

    inline void ltrim(std::string &s)
    {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
            return !std::isspace(ch);
        }));
    }

    inline void rtrim(std::string &s)
    {
        s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
                    return !std::isspace(ch);
                }).base(),
                s.end());
    }

    inline void trim(std::string &s)
    {
        ltrim(s);
        rtrim(s);
    }
}
#endif //TOYJVM_STRUTILS_H
