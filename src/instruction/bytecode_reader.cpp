#include <jvm/instruction/bytecode_reader.h>

namespace cyh {
void ByteCodeReader::SkipPadding()
{
    while (pc_ % 4 != 0) {
	Read<u1>();
    }
}
std::vector<int> ByteCodeReader::ReadInt32s(int n)
{
    std::vector<int> result(n);

    for (int i = 0; i < n; i++) {
	result[i] = Read<int>();
    }

    return result;
}

void ByteCodeReader::Reset(bytes &data,int pc){
	data_ = data;
	pc_ = pc;
}
}
