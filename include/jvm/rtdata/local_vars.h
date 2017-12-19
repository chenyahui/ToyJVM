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
	data_[index].val = ConvertToInt32<T>(val);
    }
    template <typename T>
    T Get(int index)
    {
	return ConvertFromInt32<T>(data_[index].val);
    }

private:
    std::vector<LocalSlot> data_;
};
}
#endif /* ifndef  */
