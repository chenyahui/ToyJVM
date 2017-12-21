#ifndef MY_JVM_UTILS_UNSAFE_H
#define MY_JVM_UTILS_UNSAFE_H

#include <assert.h>
#include <jvm/utils/types.h>
#include <memory.h>
#include <type_traits>
namespace cyh {
template <typename SourceType, typename ResultType>
inline ResultType ConvertAtLowLevel(SourceType s)
{
    auto s_len = sizeof(SourceType);
    auto r_len = sizeof(ResultType);

    if (std::is_same<SourceType, ResultType>::value) {
	return s;
    }
    //assert(s_len <= r_len);

    if (s_len == r_len) {
	ResultType val;
	memcpy(&val, &s, r_len);
	return val;
    } else {
	return static_cast<ResultType>(s);
    }
}

// for float, short, char , byte
template <typename T, typename R = int>
inline R ConvertToInt32(T val)
{
    assert((std::is_same<R, int32_t>::value));
    return ConvertAtLowLevel<T, int32_t>(val);
}

template <>
inline std::pair<int, int> ConvertToInt32<j_long, std::pair<int, int> >(j_long val)
{
    int low = int(val);
    int high = int(val >> 32);
    return std::make_pair(low, high);
}

template <>
inline std::pair<int, int> ConvertToInt32<j_double, std::pair<int, int> >(double val)
{
    int64_t lval = ConvertAtLowLevel<double, int64_t>(val);
    //    return ConvertToInt32<int64_t, std::pair<int, int> >(lval);
    int low = int(lval);
    int high = int(lval >> 32);
    return std::make_pair(low, high);
}

template <typename T = int, typename R>
inline R ConvertFromInt32(T val, R)
{
    assert((std::is_same<T, int32_t>::value));

    return ConvertAtLowLevel<T, R>(val);
}

template<>
inline j_long ConvertFromInt32(std::pair<int32_t, int32_t> vals, j_long)
{
    j_long l = int64_t(vals.second) << 32 | int64_t(vals.first);
    return l;
}

template<>
inline j_double ConvertFromInt32(std::pair<int32_t, int32_t> vals, j_double)
{
    j_long l = int64_t(vals.second) << 32 | int64_t(vals.first);
    return ConvertAtLowLevel<j_long, j_double>(l);
}


inline j_long Convert2IntToLong(std::pair<int32_t, int32_t> vals)
{
    j_long l = int64_t(vals.second) << 32 | int64_t(vals.first);
    return l;
}
inline j_double Convert2IntToDouble(std::pair<int, int> vals)
{
    j_long l = int64_t(vals.second) << 32 | int64_t(vals.first);
    return ConvertAtLowLevel<j_long, j_double>(l);
}
}
#endif
