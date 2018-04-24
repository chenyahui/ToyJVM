//
// Created by cyhone on 18-2-8.
//

#ifndef TOYJVM_TYPE_CAST_H
#define TOYJVM_TYPE_CAST_H

#include <assert.h>
#include <toyjvm/utilities/jvm_types.h>
#include <utility>
#include <array>

namespace jvm {

    template<typename From, typename To>
    To union_cast(From from)
    {
        union Converter {
            From from; // 注意，如果from是个int数组，由于小端序，所以第一个元素是to的最低位，这里与常识相悖
            To to;
        };

        Converter converter = {.from= from};
        return converter.to;
    }
}
#endif //TOYJVM_TYPE_CAST_H
