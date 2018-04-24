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

namespace jvm {
    class LocalSlots : boost::noncopyable {
    public:
        explicit LocalSlots(size_t slot_size)
                : slot_size_(slot_size),
                  slots_(slot_size)
        {}

        template<typename T>
        void set(size_t index, T data)
        {
            assert(index < slot_size_);
            if (use_two_slot<T>::value) {
                auto two = union_cast<T, std::array<int, 2>>(data);
                slots_[index] = boost::any(two[0]);
                slots_[index + 1] = boost::any(two[1]);
            } else {
                slots_[index] = boost::any(data);
            }
        }

        template<typename T>
        T at(size_t index) const
        {
            assert(index < slot_size_);
            if (use_two_slot<T>::value) {
                return union_cast<std::array<int, 2>, T>({at<int>(index), at<int>(index + 1)});
            }
            return boost::any_cast<T>(slots_[index]);
        }

    protected:
        template<typename T>
        struct use_two_slot {
            static const bool value = std::is_same<T, jdouble>::value || std::is_same<T, jlong>::value;
        };

    protected:
        size_t slot_size_;
        std::vector<boost::any> slots_;
    };
}
#endif //TOYJVM_LOCALSLOTS_H
