#ifndef MY_JVM_INSTRUCTION_BYTECODE_READER_H
#define MY_JVM_INSTRUCTION_BYTECODE_READER_H
#include <jvm/utils/types.h>
#include <jvm/utils/unsafe.h>

namespace cyh {
class ByteCodeReader {
public:
    ByteCodeReader() {}
    ByteCodeReader(bytes& data)
	: data_(data)
	, pc_(0)
    {
    }
    template <typename T>
    T Read()
    {
	auto num = sizeof(T);
	T result = T();
	for (decltype(num) i = 0; i < num; ++i) {
	    result |= data_[pc_ + i] << ((num - i - 1) * 8);
	}
	pc_ += num;
	return result;
    }
    void SkipPadding();
    std::vector<int> ReadInt32s(int n);
    void Reset(bytes& data, int pc);
    inline int Pc() { return pc_; }
private:
    bytes data_;
    int pc_;
};
}
#endif /* ifndef  */
