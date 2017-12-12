#ifndef MY_JVM_UTILS_FILEUTILS_H
#define MY_JVM_UTILS_FILEUTILS_H

#include <string>
#include <fstream>
#include <jvm/utils/types.h>
#include <jvm/utils/logutils.h>

namespace cyh
{
	using std::ifstream;

	inline bytes readfile(const std::string& filename){
		ifstream file(filename,ifstream::binary);
		if(!file.good()){
			throw "文件"+filename+"不存在";
		}
		bytes data;
		char c = '\0';
		int counter = 0;
		while(file.read(&c , 1)){
			if(counter++ < 4){
				log(static_cast<int>(c));
			}
			data.push_back(reinterpret_cast<u1&>(c));
		}
		log("----------");
		file.close();
		return data;
	}
}

#endif
