#include <jvm/classfile/classreader.h>
namespace cyh {
ClassReader::ClassReader(bytes& data)
    : data_(data)
    , now_(0)
{
}
ClassReader::ClassReader(const ClassReader& reader)
{
    this->data_ = reader.data_;
    this->now_ = 0;
}
ClassReader& ClassReader::operator=(const ClassReader& reader)
{
    this->data_ = reader.data_;
    this->now_ = 0;
    return *this;
}

ClassReader::~ClassReader()
{
}

std::vector<u2> ClassReader::ReadU2s()
{
    u2 num = ReadU2();
    std::vector<u2> u2s;
    for (int i = 0; i < num; ++i) {
	u2s.push_back(ReadU2());
    }
    return u2s;
}
std::vector<u1> ClassReader::ReadU1s()
{
    u2 num = ReadU2();
    return ReadU1s((u4)num);
}
std::vector<u1> ClassReader::ReadU1s(u4 num)
{
    bytes u1s;
    for (int i = 0; i < num; ++i) {
	u1s.push_back(ReadU1());
    }
    return u1s;
}
#define READ_BYTES(num)                                       \
    u##num ClassReader::ReadU##num()                          \
    {                                                         \
	u##num result = 0x0;                                  \
	for (int i = 0; i < num; ++i) {                       \
	    result |= data_[now_ + i] << ((num - i - 1) * 8); \
	}                                                     \
	now_ += num;                                          \
	return result;                                        \
    }

READ_BYTES(8)
READ_BYTES(4)
READ_BYTES(2)
READ_BYTES(1)
}
