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
    return *((ResultType*)&s);
}

template <typename T>
inline int32_t ConvertToInt32(T val)
{
    if (std::is_same<T, float>::value) {
	return ConvertAtLowLevel<float, int32_t>(val);
    } else {
	return static_cast<int32_t>(val);
    }
}

inline std::pair<int, int> ConvertToInt32(int64_t val)
{
    int low = int(val);
    int high = int(val >> 32);
    return std::make_pair(low, high);
}

inline std::pair<int, int> ConvertToInt32(double val)
{
    int64_t lval = ConvertAtLowLevel<double, int64_t>(val);
    return ConvertToInt32<int64_t>(lval);
}

template <typename T>
inline T ConvertFromInt32(int32_t val)
{
    if (std::is_same<T, float>::value) {
	return ConvertAtLowLevel<int32_t, float>(val);
    } else {
	return static_cast<T>(val);
    }
}

inline int64_t ConvertFromInt32(std::pair<int32_t, int32_t> vals)
{
    return int64_t(vals.second) << 32 | int64_t(vals.first)
}

inline double ConvertFromInt32(intstd::pair<int32_t, int32_t> vals)
{
    int64_t l_result = ConvertFromInt32(vals);

    return ConvertAtLowLevel<int64_t, double>(val);
}
}
#endif
