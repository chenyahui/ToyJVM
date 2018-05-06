//
// Created by cyhone on 18-4-16.
//

#ifndef TOYJVM_OPERAND_STACK_H
#define TOYJVM_OPERAND_STACK_H

#include <boost/core/noncopyable.hpp>
#include <boost/any.hpp>
#include <vector>
#include <toyjvm/runtime/local_slots.h>
#include <iostream>

namespace jvm {
    class OperandStack : public LocalSlots {
    public:
        explicit OperandStack(size_t max_stack_num)
                : LocalSlots(max_stack_num)
        {}

        template<typename T>
        void push(T data)
        {
            set<T>(stack_num_, data);
            stack_num_ += use_two_slot<T>::value ? 2 : 1;
        }

        template<typename T = boost::any>
        T pop()
        {
            size_t index = stack_num_ - (use_two_slot<T>::value ? 2 : 1);
            auto result = at<T>(index);
            stack_num_ = index;
            return result;
        }

        jref getRefFromTop(int offset)
        {
            return at<jref>(slots_.size() - offset - 1);
        }

    private:
        size_t stack_num_ = 0;
    };
};
#endif //TOYJVM_OPERAND_STACK_H
