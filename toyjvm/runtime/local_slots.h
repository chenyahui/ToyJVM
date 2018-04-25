//
// Created by cyhone on 18-4-16.
//

#ifndef TOYJVM_LOCAL_SLOTS_H
#define TOYJVM_LOCAL_SLOTS_H

#include <boost/core/noncopyable.hpp>
#include <vector>
#include <boost/any.hpp>
#include <assert.h>
#include <toyjvm/utilities/jvm_types.h>
#include <array>
#include <toyjvm/utilities/type_cast.h>
#include <type_traits>
#include <iostream>

namespace jvm {
    class LocalSlots : boost::noncopyable {
    protected:
        template<typename T>
        struct use_two_slot {
            static const bool value = std::is_same<T, jdouble>::value || std::is_same<T, jlong>::value;
        };

    public:
        explicit LocalSlots(size_t slot_size)
                : slot_size_(slot_size),
                  slots_(slot_size)
        {}


        template<typename T, typename std::enable_if<!use_two_slot<T>::value>::type * = nullptr>
        void set(size_t index, T data)
        {
            slots_[index] = boost::any(data);
        }

        template<class T, typename std::enable_if<use_two_slot<T>::value>::type * = nullptr>
        void set(size_t index, T data)
        {
            auto two = union_cast<T, std::array<u4, 2>>(data);
            slots_[index] = boost::any(two[0]);
            slots_[index + 1] = boost::any(two[1]);
        };


        template<typename T, typename std::enable_if<use_two_slot<T>::value>::type * = nullptr>
        T at(size_t index) const
        {
            return union_cast<std::array<u4, 2>, T>({at<u4>(index), at<u4>(index + 1)});
        }

        template<typename T, typename std::enable_if<!use_two_slot<T>::value>::type * = nullptr>
        T at(size_t index) const
        {
            return boost::any_cast<T>(slots_[index]);
        }


    protected:
        size_t slot_size_;
        std::vector<boost::any> slots_;
    };
}
#endif //TOYJVM_LOCALSLOTS_H
