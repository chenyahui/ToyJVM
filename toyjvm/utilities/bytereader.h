//
// Created by cyhone on 18-1-30.
//

#ifndef TOYJVM_BYTEREADER_H
#define TOYJVM_BYTEREADER_H

#include <boost/noncopyable.hpp>
#include <toyjvm/utilities/jvm_types.h>
#include <toyjvm/utilities/type_cast.h>
#include <algorithm>

namespace jvm {
    class ByteReader : boost::noncopyable {
    public:
        explicit ByteReader(bytes data)
                : data_(std::move(data))
        {}

        template<typename T>
        T read()
        {
            auto num = sizeof(T);
            std::array<u1, sizeof(T)> raw_byte;
            // 因为小端序，所以要倒序拷贝
            std::reverse_copy(data_.begin() + pc_, data_.begin() + pc_ + num, raw_byte.begin());
            pc_ += num;
            return union_cast<std::array<u1, sizeof(T)>, T>(raw_byte);
        }


        template<typename Counter, typename Item>
        std::vector<Item> batchRead()
        {
            Counter count = read<Counter>();
            std::vector<Item> result(count);

            for (auto i = 0; i < count; i++) {
                result[i] = read<Item>();
            }

            return result;
        };

        template<typename T>
        std::vector<T> batchRead(int count)
        {
            std::vector<T> result(count);

            for (auto i = 0; i < count; i++) {
                result[i] = read<T>();
            }

            return result;
        }

    protected:
        bytes data_;
        int pc_ = 0;
    };

}

#endif //NEWJVM_BASEREADER_H
