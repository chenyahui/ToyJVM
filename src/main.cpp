#include <glog/logging.h>
#include <iostream>
#include <jvm/classfile/classfile.h>
#include <jvm/instruction/base_instruction.h>
#include <jvm/instruction/bytecode_reader.h>
#include <jvm/interpret.h>
#include <jvm/rtdata/class_loader.h>
#include <jvm/rtdata/jvm_thread.h>
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
    google::InitGoogleLogging(argv[0]);
    std::string filename(argv[1]);
    FLAGS_logtostderr = 1;
    try {
	cyh::startJvm(filename);
    } catch (char const* e) {
	cout << e << endl;
    } catch (std::string& e) {
	cout << e << endl;
    } catch (std::exception& e) {
	cout << e.what() << endl;
    } catch (...) {
	cout << "OMG! an unexpected exception has been caught" << endl;
    }
    return 0;
}
