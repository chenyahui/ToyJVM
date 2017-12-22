#include <iostream>
#include <jvm/classfile/classfile.h>
#include <jvm/instruction/base_instruction.h>
#include <jvm/instruction/bytecode_reader.h>
#include <jvm/rtdata/jvm_thread.h>
#include <jvm/utils/fileutils.h>

#include <typeinfo>
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
namespace cyh {
void loop(JThread* thread, bytes& data);
void interpert(MemberInfo* method_info)
{
    auto code_attr = method_info->CodeAttribute();
    JThread* thread = new JThread();
    thread->NewAndPushFrame(code_attr->max_locals_, code_attr->max_stack_);
    loop(thread, code_attr->code_);
}

void printFrame(int pc, Instruction* inst)
{
    cout << "pc :" << pc
	 << " " << typeid(*inst).name() << endl;
}

void printLocalVar(LocalVarRefs& localvars)
{
    auto data = localvars.InnerData();
    cout << "局部变量表" << endl;
    for (auto item : data) {
	cout << item.val << endl;
    }
}

void printOpStack(OperandStack& opstack)
{
    auto data = opstack.InnerData();

    cout << "操作数栈" << endl;

    while (!data.empty()) {
	cout << data.top().val << endl;
	data.pop();
    }
}
void loop(JThread* thread, bytes& data)
{
    auto frame = thread->PopFrame();
    auto reader = ByteCodeReader();

    while (true) {
	try {
	    cout << "==========================" << endl;
	    int pc = frame->NextPc();
	    thread->SetPc(pc);

	    reader.Reset(data, pc);
	    auto opcode = reader.Read<u1>();
	    cout << "opcode:" << int(opcode) << endl;
	    Instruction* inst = InstructionFactory(opcode);
	    inst->FetchOperands(reader);
	    frame->SetNextPc(reader.Pc());

	    printFrame(pc, inst);
	    inst->Execute(frame);

	    printLocalVar(frame->LocalVars());
	    printOpStack(frame->OpStack());
	} catch (...) {

	    break;
	}
    }

    cout << "结束，局部变量表：" << endl;
    for (auto item : frame->LocalVars().InnerData()) {
	cout << item.val << endl;
    }
}

MemberInfo* GetMainFunc(ClassFile* klass)
{
    for (auto item : klass->methods) {
	//cout << item->MemberName()<<endl;
	if (item->MemberName() == "main") {
	    return item;
	}
    }

    throw "can't find main";
}

void startJvm(const char* filename)
{

    cyh::bytes data = cyh::readfile(filename);
    ClassFile* klass = new ClassFile(data);
    klass->Parse();

    auto mainfunc = GetMainFunc(klass);

    interpert(mainfunc);
}
}
int main(int argc, char* argv[])
{
    try {
	cyh::startJvm("/home/cyhone/Guass.class");
    } catch (char const* e) {
	cout << e << endl;
    } catch (std::string& e) {
	cout << e << endl;
    } catch (...) {
	cout << "OMG! an unexpected exception has been caught" << endl;
    }
    return 0;
}
