#ifndef MY_JVM_UTILS_BITUTILS_H
#define MY_JVM_UTILS_BITUTILS_H

#include <memory.h>
#include <assert.h>

#include <jvm/utils/types.h>
namespace cyh{
	template<typename SourceType, typename ResultType, size_t len>
	inline ResultType ConvertBytesToNumeric(SourceType value){
		ResultType val;
		memcpy(&val,&value,len);
		return val;
	}

        const auto& ConvertU4ToFloat = ConvertBytesToNumeric<u4,float,4>;
	const auto& ConvertU8ToDouble = ConvertBytesToNumeric<u8,double,8>;
	const auto& ConvertU8ToLong = ConvertBytesToNumeric<u8,long,8>;

	inline bool IsZeroAtByte(u1 byte, int position){
		assert(position <=7 && position >= 0);
		return (1 << (7 - position) & byte) == 0;
	}
}
#endif
