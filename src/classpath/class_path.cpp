#include <jvm/classpath/classpath.h>
#include <jvm/utils/fileutils.h>
#include <jvm/utils/strutils.h>

using namespace cyh;

bytes ClassPath::ReadClass(std::string class_name)
{
    if (starts_with(class_name, "java/")) {
	class_name = "/home/cyhone/rt/" + class_name;
    }
    if (!ends_with(class_name, ".class")) {
	class_name += ".class";
    }
    return readfile(class_name);
}
