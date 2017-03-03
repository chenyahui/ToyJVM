//
// Created by cyhone on 17-2-26.
//

#pragma once

#include <exception>
#include <string>

namespace cyh {

    class ClassNotFoundException : public std::exception {
    public:
        ClassNotFoundException(std::string const &message) : msg_(message) {}

        virtual char const *what() const noexcept { return msg_.c_str(); }

    private:
        std::string msg_;
    };

    class ClassFormatError : public std::exception {
    public:
        ClassFormatError(std::string const &message) : msg_(message) {}

        virtual char const *what() const noexcept { return msg_.c_str(); }

    private:
        std::string msg_;
    };
}