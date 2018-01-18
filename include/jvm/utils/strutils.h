#ifndef TOYJVM_UTILS_STRUTILS_H
#define TOYJVM_UTILS_STRUTILS_H
#include <string>
#include <algorithm>
namespace cyh {
inline bool ends_with(std::string const& value, std::string const& ending)
{
    if (ending.size() > value.size())
	return false;
    return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
}
inline bool starts_with(std::string const& value, std::string const& starting)
{
    if (starting.size() > value.size())
	return false;
    return std::equal(starting.begin(), starting.end(), value.begin());
}
// trim from start (in place)
inline void ltrim(std::string& s)
{
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
		return !std::isspace(ch);
	    }));
}

// trim from end (in place)
inline void rtrim(std::string& s)
{
    s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
		return !std::isspace(ch);
	    }).base(),
	s.end());
}

// trim from both ends (in place)
inline void trim(std::string& s)
{
    ltrim(s);
    rtrim(s);
}
}

#endif /* end of include guard: TOYJVM_UTILS_STRUTILS_H */
