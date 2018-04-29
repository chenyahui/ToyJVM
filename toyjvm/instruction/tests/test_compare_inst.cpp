//
// Created by cyhone on 18-4-28.
//

#include <gtest/gtest.h>
#include <toyjvm/instruction/compare_instructions.h>
#include <toyjvm/runtime/jvm_reference.h>
#include "test_inst_context.h"

using namespace jvm;
using namespace jvm_test;

TEST_F(InstTestContext, REF_CMP)
{
    {
        bytes data = {0, 3};
        auto reader = std::unique_ptr<ByteCodeReader>(new ByteCodeReader(data));
        auto inst = std::unique_ptr<IF_ACMPNE_Instruction>(new IF_ACMPNE_Instruction());

        std::shared_ptr<JvmObject> obj = nullptr;
        std::equal_to<jref> cmp;
        if (cmp(obj, 0)) {
            opstack_->push<jref>(obj);
            opstack_->push<jref>(obj);

            EXPECT_EQ(frame_->nextPc(), 0);
        }
    }
}

TEST_F(InstTestContext, IFLT_IF_ICMPLT)
{
    {
        bytes data = {0, 3};
        auto reader = std::unique_ptr<ByteCodeReader>(new ByteCodeReader(data));
        auto iflt_instruction = std::unique_ptr<IFLT_Instruction>(new IFLT_Instruction());
        opstack_->push<int>(10);
        iflt_instruction->run(*reader, *frame_);
        EXPECT_EQ(frame_->nextPc(), 0);
        frame_->setNextPc(0);
    }

    {
        bytes data = {0, 3};
        auto reader = std::unique_ptr<ByteCodeReader>(new ByteCodeReader(data));
        auto iflt_instruction = std::unique_ptr<IFLT_Instruction>(new IFLT_Instruction());
        opstack_->push<int>(-10);
        iflt_instruction->run(*reader, *frame_);
        EXPECT_EQ(frame_->nextPc(), 3);
        frame_->setNextPc(0);
    }

    {
        bytes data = {0, 3};
        auto reader = std::unique_ptr<ByteCodeReader>(new ByteCodeReader(data));
        auto iflt_instruction = std::unique_ptr<IF_ICMPLT_Instruction>(new IF_ICMPLT_Instruction());
        opstack_->push<int>(1);
        opstack_->push<int>(2);
        iflt_instruction->run(*reader, *frame_);
        EXPECT_EQ(frame_->nextPc(), 3);
        frame_->setNextPc(0);
    }

    {
        bytes data = {0, 3};
        auto reader = std::unique_ptr<ByteCodeReader>(new ByteCodeReader(data));
        auto iflt_instruction = std::unique_ptr<IF_ICMPLT_Instruction>(new IF_ICMPLT_Instruction());
        opstack_->push<int>(2);
        opstack_->push<int>(1);
        iflt_instruction->run(*reader, *frame_);
        EXPECT_EQ(frame_->nextPc(), 0);
        frame_->setNextPc(0);
    }
}

TEST_F(InstTestContext, DCMPL)
{
    // 上下文参数设置
    bytes data = {};
    auto reader = std::unique_ptr<ByteCodeReader>(new ByteCodeReader(data));

    DCMPL_Instruction *dcmpl_instruction = new DCMPL_Instruction();

    // 第一组
    opstack_->push<jdouble>(1.0);
    opstack_->push<jdouble>(1.1);
    dcmpl_instruction->run(*reader, *frame_);
    EXPECT_EQ(opstack_->pop<int>(), -1);

    opstack_->push<jdouble>(1.0);
    opstack_->push<jdouble>(1.0);
    dcmpl_instruction->run(*reader, *frame_);
    EXPECT_EQ(opstack_->pop<int>(), 0);

    opstack_->push<jdouble>(1.2);
    opstack_->push<jdouble>(1.0);
    dcmpl_instruction->run(*reader, *frame_);
    EXPECT_EQ(opstack_->pop<int>(), 1);
}
