#include <cstdio>
#include <iostream>
#include <jvm/interpret.h>
#include <jvm/native/registy.h>
#include <jvm/rtdata/class_loader.h>
#include <jvm/utils/instructionutils.h>
#include <typeinfo>
using namespace std;
#ifdef DEBUG
const bool is_log = true;
#else
const bool is_log = false;
#endif
namespace cyh {
void loop(JThread* thread);
void interpret(JMethod* method)
{
    JThread* thread = new JThread();
    auto jframe = new JFrame(thread, method);
    thread->PushFrame(jframe);
    loop(thread);
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
    cout << "共有: " << data.size() << "个" << endl;

    while (!data.empty()) {
	cout << data.top().val << endl;
	data.pop();
    }
}

void log_frame(JFrame* frame)
{
    if (is_log) {
	printLocalVar(frame->LocalVars());
	printOpStack(frame->OpStack());
    }
}
void loop(JThread* thread)
{
    auto reader = ByteCodeReader();
    while (true) {
	auto frame = thread->TopFrame();

	int pc = frame->NextPc();
	thread->SetPc(pc);

	reader.Reset(frame->jmethod()->code(), pc);
	auto opcode = reader.Read<u1>();

	if (is_log) {
	    cout << "==========================" << endl;
	    auto method = frame->jmethod();
	    cout << "now method : " << method->jclass()->name() << "->" << method->name() << "->" << method->descriptor() << endl;
	    cout << ">>>>>>>" << GetInstrutionByTag(opcode) << endl;
	}

	Instruction* inst = InstructionFactory(opcode);
	inst->FetchOperands(reader);
	frame->SetNextPc(reader.Pc());

	inst->Execute(frame);
	log_frame(frame);

	if (thread->IsStackEmpty()) {
	    // cout << "栈空了，退出！" << endl;
	    break;
	}
    }

    /*cout << "结束，局部变量表：" << endl;*/
    //for (auto item : frame->LocalVars().InnerData()) {
    //cout << item.val << endl;
    /*}*/
}

JMethod* GetMainFunc(JClass* jclass)
{
    for (auto item : jclass->methods()) {
	//cout << item->MemberName()<<endl;
	if (item->name() == "main") {
	    return item;
	}
    }

    throw "can't find main";
}

void startJvm(std::string& class_name)
{
    InitNativeMethods();
    ClassLoader* loader = new ClassLoader();
    auto jclass = loader->LoadClass(class_name);

    std::string config_json = "/home/cyhone/MyProject/ToyJVM/etc/instructions.json";
    LoadInstructionConfig(config_json);

    interpret(GetMainFunc(jclass));
}
}
