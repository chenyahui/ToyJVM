#ifndef MY_JVM_RUNTIMEAREA_LOCALVARS_H
#define MY_JVM_RUNTIMEAREA_LOCALVARS_H
#include <jvm/rtdata/jvm_reference.h>
#include <jvm/utils/unsafe.h>
#include <utility>
#include <vector>

namespace cyh {
union LocalSlot {
    int32_t val;
    j_ref ref;
};

class LocalVarRefs {

public:
    LocalVarRefs(int max_locals)
	: max_locals_(max_locals)
	, data_(max_locals)
    {
    }
    template <typename T>
    void Set(int index, T val)
    {
	data_[index].val = ConvertToInt32<T, int>(val);
    }

    template <typename T>
    T Get(int index)
    {
	assert(index < data_.size());
	return ConvertFromInt32<int, T>(data_[index].val, 0);
    }

    inline std::vector<LocalSlot>& InnerData() { return data_; }

    inline JObject* GetThis()
    {
	return dynamic_cast<JObject*>(data_[0].ref);
    }

private:
    int max_locals_;
    std::vector<LocalSlot> data_;
};
}

namespace cyh {
template <>
inline void LocalVarRefs::Set<j_long>(int index, j_long val)
{
    auto vals = ConvertToInt32<j_long, std::pair<int, int> >(val);
    data_[index].val = vals.first;
    data_[index + 1].val = vals.second;
}

template <>
inline void LocalVarRefs::Set<j_double>(int index, j_double val)
{
    auto vals = ConvertToInt32<j_double, std::pair<int, int> >(val);
    data_[index].val = vals.first;
    data_[index + 1].val = vals.second;
}

template <>
inline void LocalVarRefs::Set<LocalSlot>(int index, LocalSlot slot)
{
    data_[index] = slot;
}
template <>
inline void LocalVarRefs::Set<JObject*>(int index, JObject* obj)
{
    data_[index].ref = obj;
}

template <>
inline void LocalVarRefs::Set<j_ref>(int index, j_ref ref)
{
    data_[index].ref = ref;
}
template <>
inline j_long LocalVarRefs::Get<j_long>(int index)
{
    int high = data_[index + 1].val;
    int low = data_[index].val;
    auto vals = std::make_pair(high, low);
    return Convert2IntToLong(vals);
}

template <>
inline j_double LocalVarRefs::Get<j_double>(int index)
{
    auto high = data_[index + 1].val;
    auto low = data_[index].val;
    auto vals = std::make_pair(high, low);
    return Convert2IntToDouble(vals);
}

template <>
inline j_ref LocalVarRefs::Get<j_ref>(int index)
{
    return data_[index].ref;
}
template <>
inline JBaseArray* LocalVarRefs::Get<JBaseArray*>(int index)
{
    return dynamic_cast<JBaseArray*>(data_[index].ref);
}
template <>
inline JObject* LocalVarRefs::Get<JObject*>(int index)
{
    return dynamic_cast<JObject*>(data_[index].ref);
}
}

#endif /* ifndef  */
