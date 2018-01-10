#ifndef TOYJVM_UTILS_STRUTILS_H
#define TOYJVM_UTILS_STRUTILS_H
#include <string>
namespace cyh {
inline bool ends_with(std::string const& value, std::string const& ending)
{
    if (ending.size() > value.size())
	return false;
    return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
}
}

#endif /* end of include guard: TOYJVM_UTILS_STRUTILS_H */
