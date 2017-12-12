#ifndef MY_JVM_UTILS_UTF8UTILS_H
#define MY_JVM_UTILS_UTF8UTILS_H

#include <string>
#include <sstream>
#include <jvm/utils/types.h>
#include <jvm/utils/bitutils.h>
#include <jvm/utils/logutils.h>
namespace cyh{

	// modified-utf8 to c++ string
	inline std::string MUtf8ToString(bytes& data){
		std::stringstream result;
		bool flag = true;
		for(auto item : data){
       /*                 log("item");*/
			/*log((char)item);*/
			if (item <= 127){
				flag = false;
				result << char(item);
			}
		}

		return result.str();
	}
}
#endif
