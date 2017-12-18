#ifndef MY_JVM_RUNTIMEAREA_LOCALVARS_H
#define MY_JVM_RUNTIMEAREA_LOCALVARS_H
#include <jvm/utils/unsafe.h>
#include <vector>

namespace cyh {
union LocalSlot {
    int32_t val;
    j_ref ref;
};
class LocalVarRefs {
public:
    template <typename T>
    void Set(int index, T val)
    {
	if (std::is_same<T, double>::value || std::is_same<T, int64_t>::value) {
	    auto vals = ConvertToInt32<T>(val);

	    data_[index].val = vals.first;
	    data_[index + 1].val = vals.second;
	} else if (std::is_same<T, j_ref>::value) {
	    data_[index].ref = val;
	} else {
	    data_[index].val = ConvertToInt32<T>(val);
	}
    }
    template <typename T>
    T Get(int index)
    {
	if (std::is_same<T, double>::value || std::is_same<T, int64_t>::value) {
	    auto high = data_[index + 1].val;
	    auto low = data_[index].val;

	    return ConvertFromInt32<T>(high, low);

	} else if (std::is_same<T, j_ref>::value) {
	    return data_[index].ref;
	} else {
	    return ConvertFromInt32<T>(data_[index].val);
	}
    }

private:
    const std::vector<LocalSlot> data_;
};
}
#endif /* ifndef  */
