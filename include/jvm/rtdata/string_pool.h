#ifndef TOYJVM_RTDATA_STRING_POOL_H
#define TOYJVM_RTDATA_STRING_POOL_H
#include <jvm/utils/types.h>
#include <string>
#include <vector>

namespace cyh {
class JObject;
class ClassLoader;
JObject* GetStringFromPool(ClassLoader*, std::string str);
std::string TransJString(JObject*);
std::vector<j_char> StringToUtf16Arr(std::string& str);
}

#endif /* end of include guard: TOYJVM_RTDATA_STRING_POOL_H */
