#include <jvm/native/array_copy.h>
#include <jvm/rtdata/jvm_frame.h>
#include <jvm/rtdata/jvm_reference.h>
#include <jvm/utils/strutils.h>

namespace cyh {
static bool CheckArrayCopy(JBaseArray* src, JBaseArray* dest);

void arraycopy(JFrame* frame)
{
    auto& local_vars = frame->LocalVars();
    auto src = local_vars.Get<JBaseArray*>(0);
    auto src_pos = local_vars.Get<int>(1);
    auto dest = local_vars.Get<JBaseArray*>(2);
    auto dest_pos = local_vars.Get<int>(3);
    auto length = local_vars.Get<int>(4);

    if (src == NULL || dest == NULL) {
	throw "array copy null pointer";
    }

    if (!CheckArrayCopy(src, dest)) {
	throw "array store exception";
    }

    if (src_pos < 0 || dest_pos < 0 || length < 0
	|| src_pos + length > src->array_length()
	|| dest_pos + length > dest->array_length()) {
	throw "index bounds exception";
    }
}

bool CheckArrayCopy(JBaseArray* src, JBaseArray* dest)
{
    auto src_class = src->jclass();
    auto dest_class = dest->jclass();

    if (!src_class->IsArray() || !dest_class->IsArray()) {
	return false;
    }

    if (src_class->ComponentClass()->IsPrimitive() && dest_class->ComponentClass()->IsPrimitive()) {
	return src_class == dest_class;
    }

    return true;
}

#define ARRAY_CP(NAME, TYPE)                                                                         \
    prefix = "[" #NAME "";                                                                           \
    if (starts_with(src->jclass()->name(), prefix)) {                                                \
	auto src_arr = dynamic_cast<JArray<TYPE>*>(src);                                             \
	auto dest_arr = dynamic_cast<JArray<TYPE>*>(dest);                                           \
                                                                                                     \
	auto src_begin = src_arr->raw_data().begin();                                                \
	auto dest_it = dest_arr->raw_data().begin() + dest_pos;                                      \
	for (auto src_it = src_begin + src_pos; src_it != src_begin + length; ++src_it, ++dest_it) { \
	    *src_it = *dest_it;                                                                      \
	}                                                                                            \
	return;                                                                                      \
    }

void ArrayCopy(JBaseArray* src, JBaseArray* dest, int src_pos, int dest_pos, int length)
{
    std::string prefix;
    ARRAY_CP(Z, bool)
    ARRAY_CP(B, j_byte)
    ARRAY_CP(C, j_char)
    ARRAY_CP(S, j_short)
    ARRAY_CP(I, j_int)
    ARRAY_CP(J, j_long)
    ARRAY_CP(F, j_float)
    ARRAY_CP(D, j_double)
    ARRAY_CP(L, j_ref);
}
}
