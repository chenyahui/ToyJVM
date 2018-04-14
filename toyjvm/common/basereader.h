//
// Created by cyhone on 18-1-30.
//

#ifndef TOYJVM_BASEREADER_H
#define TOYJVM_BASEREADER_H

#include <boost/noncopyable.hpp>
#include <toyjvm/common/jvm_types.h>
#include <toyjvm/common/type_cast.h>

namespace jvm {
    class BaseReader;

    class BaseReader : boost::noncopyable {
    public:
        BaseReader(const BaseReader &reader)
                : data_(reader.data_),
                  pc_(reader.pc_)
        {}

        explicit BaseReader(bytes &data)
                : data_(data)
        {}

        template<typename T>
        T read()
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
        float read<float>()
        {
            auto raw_bits = read<int>();
            return bits_cast<int, float>(raw_bits);
        };

        template<>
        double read<double>()
        {
            auto raw_bits = read<long>();
            return bits_cast<long, double>(raw_bits);
        };

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
    private:
        bytes &data_;
        int pc_ = 0;
    };
}

#endif //NEWJVM_BASEREADER_H
