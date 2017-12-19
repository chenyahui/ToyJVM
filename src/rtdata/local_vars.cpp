#include <jvm/rtdata/local_vars.h>

namespace cyh {
template <>
void LocalVarRefs::Set<j_long>(int index, j_long val)
{
    auto vals = ConvertToInt32<j_long, std::pair<int, int> >(val);

    data_[index].val = vals.first;
    data_[index + 1].val = vals.second;
}
template <>
void LocalVarRefs::Set<j_double>(int index, j_double val)
{
    auto vals = ConvertToInt32<j_double, std::pair<int, int> >(val);

    data_[index].val = vals.first;
    data_[index + 1].val = vals.second;
}
template <>
void LocalVarRefs::Set<j_ref>(int index, j_ref ref)
{
    data_[index].ref = ref;
}

template <>
j_long LocalVarRefs::Get<j_long>(int index)
{
    auto high = data_[index + 1].val;
    auto low = data_[index].val;

    return ConvertFromInt32<std::pair<int,int>, j_long>(std::make_pair(high, low),  0);
}
template <>
j_double LocalVarRefs::Get<j_double>(int index)
{
    auto high = data_[index + 1].val;
    auto low = data_[index].val;

    return ConvertFromInt32<std::pair<int,int>, j_double>(std::make_pair(high, low),  0);
}
template <>
j_ref LocalVarRefs::Get<j_ref>(int index)
{
    return data_[index].ref;
}}
