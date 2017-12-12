#ifndef MY_JVM_EXCEPITON_EXCEPTIONS_H
#define MY_JVM_EXCEPITON_EXCEPTIONS_H

#include <exception>

namespace cyh{
	class ClassFileException: public std::exception
	{
		virtual const char* what() const throw()
		{
			return "My exception happened";
		}
	};
}
#endif
