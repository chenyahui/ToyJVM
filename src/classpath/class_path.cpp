#include <jvm/classpath/classpath.h>
#include <jvm/utils/fileutils.h>
#include <jvm/utils/strutils.h>

using namespace cyh;

bytes ClassPath::ReadClass(std::string class_name)
{
    if (class_name == "java/lang/Object") {
	class_name = "/home/cyhone/Object";
    }

    if (!ends_with(class_name, ".class")) {
	class_name += ".class";
    }
    return readfile(class_name);
}
