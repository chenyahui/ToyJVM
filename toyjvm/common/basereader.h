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
        explicit BaseReader(bytes data)
                : data_(std::move(data))
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

    private:
        bytes data_;
        int pc_ = 0;
    };

    template<>
    double BaseReader::read<double>();

    template<>
    float BaseReader::read<float>();
}

#endif //NEWJVM_BASEREADER_H
