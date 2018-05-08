//
// Created by cyhone on 18-5-8.
//

#ifndef TOYJVM_ALL_STATIC_H
#define TOYJVM_ALL_STATIC_H

#include <boost/noncopyable.hpp>

namespace jvm {
    class AllStatic : public boost::noncopyable {
    private:
        AllStatic() = delete;

        ~AllStatic() = delete;
    };
}
#endif //TOYJVM_ALL_STATIC_H
