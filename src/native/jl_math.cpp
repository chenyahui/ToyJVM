#include <jvm/native/jl_math.h>
#include <jvm/rtdata/jvm_frame.h>
#include <jvm/utils/unsafe.h>
namespace cyh {
template <typename T1, typename T2>
void baseTypeToBits(JFrame* frame)
{
    auto sval = frame->LocalVars().Get<T1>(0);
    auto dval = ConvertAtLowLevel<T1, T2>(sval);
    frame->OpStack().Push<T2>(dval);
}
void floatToRawIntBits(JFrame* frame)
{
    baseTypeToBits<float, int>(frame);
}
void doubleToRawLongBits(JFrame* frame)
{
    baseTypeToBits<double, long>(frame);
}
void longBitsToDouble(JFrame* frame)
{
    baseTypeToBits<long, double>(frame);
}
}
