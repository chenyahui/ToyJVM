#ifndef TOYJVM_RTDATA_STRING_POOL_H
#define TOYJVM_RTDATA_STRING_POOL_H
#include <string>
namespace cyh {
class JObject;
class ClassLoader;
JObject* GetStringFromPool(ClassLoader*, std::string str);
std::string TransJString(JObject*);
}

#endif /* end of include guard: TOYJVM_RTDATA_STRING_POOL_H */
