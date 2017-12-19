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
R ConvertToInt32(T val)
{
    assert((std::is_same<R, int32_t>::value));
    return ConvertAtLowLevel<T, int32_t>(val);
}

template <>
std::pair<int, int> ConvertToInt32<j_long, std::pair<int, int> >(j_long val)
{
    int low = int(val);
    int high = int(val >> 32);
    return std::make_pair(low, high);
}

template <>
std::pair<int, int> ConvertToInt32<j_double, std::pair<int, int> >(double val)
{
    int64_t lval = ConvertAtLowLevel<double, int64_t>(val);
    return ConvertToInt32<int64_t, std::pair<int, int> >(lval);
}

template <typename T = int, typename R>
R ConvertFromInt32(T val, int)
{
    assert((std::is_same<T, int32_t>::value));
    return ConvertAtLowLevel<int32_t, R>(val);
}

j_long ConvertFromInt32(std::pair<int32_t, int32_t> vals, j_long)
{
    j_long l = int64_t(vals.second) << 32 | int64_t(vals.first);
    return l;
}
j_double ConvertFromInt32(std::pair<int32_t, int32_t> vals, j_double)
{
    auto l = ConvertFromInt32<std::pair<int, int>, j_long>(vals, 0);
    return ConvertAtLowLevel<j_long, j_double>(l);
}
}
#endif
