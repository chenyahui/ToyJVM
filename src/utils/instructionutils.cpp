#include <fstream>
#include <iostream>
#include <jvm/utils/instructionutils.h>
#include <jvm/utils/strutils.h>
#include <regex>

namespace cyh {

int HexCharToInt(char hex_char);
int HexStrToInt(std::string hex_str);

static std::unordered_map<int, std::string> Instructions;
std::regex match_regex("\"0x(\\w{2})\":\"(\\w+)\",?");

using map_pair = std::unordered_map<int, std::string>::value_type;
void LoadInstructionConfig(std::string& filename)
{
    std::ifstream file(filename);
    std::string line;
    while (std::getline(file, line)) {
	if (line.find("{") == std::string::npos && line.find("}") == std::string::npos) {
	    trim(line);
	    std::smatch matches;
	    if (std::regex_search(line, matches, match_regex)) {
		Instructions.insert(map_pair(HexStrToInt(matches[1].str()), matches[2].str()));
	    } else {
		std::cout << "#" << line << "#" << std::endl;
		throw "匹配失败";
	    }
	}
    }
}

int HexStrToInt(std::string hex_str)
{
    return HexCharToInt(hex_str[0]) * 16 + HexCharToInt(hex_str[1]);
}

int HexCharToInt(char hex_char)
{
    if (std::isdigit(hex_char)) {
	return hex_char - '0';
    }

    if ('A' <= hex_char && 'Z' >= hex_char) {
	return hex_char - 'A' + 10;
    }

    if ('a' <= hex_char && 'z' >= hex_char) {
	return hex_char - 'a' + 10;
    }

    throw "不合法的16进制串";
}
std::string& GetInstrutionByTag(int tag)
{
    return Instructions[tag];
}
}
