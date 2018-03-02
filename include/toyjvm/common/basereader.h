//
// Created by cyhone on 18-1-30.
//

#ifndef TOYJVM_BASEREADER_H
#define TOYJVM_BASEREADER_H

#include <boost/noncopyable.hpp>
#include <toyjvm/common/jvm_types.h>
#include <toyjvm/common/type_cast.h>

namespace jvm {
    class BaseReader : boost::noncopyable {
    public:
        BaseReader()
        {}

        explicit BaseReader(bytes &data)
                : data_(data)
        {}

        // TODO float and double
        template<typename T>
        T Read()
        {
            auto num = sizeof(T);

            T result = T();
            for (decltype(num) i = 0; i < num; ++i) {
                result |= data_[pc_ + i] << ((num - i - 1) * 8);
            }

            pc_ += num;
            return result;
        }

        template<>
        float Read<float>()
        {
            auto raw_bits = Read<int>();
            return bits_cast<int, float>(raw_bits);
        };

        template<>
        double Read<double>()
        {
            auto raw_bits = Read<long>();
            return bits_cast<long, double>(raw_bits);
        };

        template<typename Counter, typename Item>
        std::vector<Item> BatchRead()
        {
            Counter count = Read<Counter>();
            std::vector<Item> result(count);

            for (auto i = 0; i < count; i++) {
                result[i] = Read<Item>();
            }

            return result;
        };
    private:
        bytes data_;
        int pc_ = 0;
    };
}

#endif //NEWJVM_BASEREADER_H
