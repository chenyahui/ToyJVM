#include <iostream>
#include <jvm/classfile/classfile.h>
#include <jvm/utils/fileutils.h>
#include <vector>
using namespace std;

template <typename T>
void println(std::string name, T value)
{
    cout << name << value << endl;
}
void println(std::string name, std::vector<std::string> items)
{
    cout << name << endl;
    for (auto item : items) {
	cout << item << " ";
    }
    cout << endl;
}

void print_class_info(cyh::ClassFile c)
{
    println("Class: ", c.ClassName());
    println("Super Class: ", c.SuperClassName());
    println("AccessFlags: ", c.AccessFlags());

    println("Interfaces: ", c.InterfaceNames());
    println("Methods: ", c.MethodNames());
    println("Fields: ", c.FieldNames());
}
int main(int argc, char* argv[])
{
    try {
	cyh::bytes data = cyh::readfile("/home/cyhone/String.class");
	cyh::ClassFile classfile(data);
	classfile.Parse();
	print_class_info(classfile);

    } catch (char const* e) {
	cout << e << endl;
    } catch (std::string& e) {
	cout << e << endl;
    } catch (...) {
	cout << "OMG! an unexpected exception has been caught" << endl;
    }
    return 0;
}
