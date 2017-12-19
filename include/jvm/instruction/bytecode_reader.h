#include <jvm/utils/types.h>
#include <jvm/utils/unsafe.h>

namespace cyh {
class ByteCodeReader {
public:
    template <typename T>
    T Read()
    {
	auto num = sizeof(T);
	T result;
	for (decltype(num) i = 0; i < num; ++i) {
	    result |= data_[pc_ + i] << ((num - i - 1) * 8);
	}
	pc_ += num;
	return result;
    }
    void SkipPadding();
    std::vector<int> ReadInt32s(int n);

private:
    bytes data_;
    int pc_;
};
}
