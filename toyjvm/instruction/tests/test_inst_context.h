//
// Created by cyhone on 18-4-29.
//

#ifndef TOYJVM_TEST_INST_CONTEXT_H
#define TOYJVM_TEST_INST_CONTEXT_H

#include <gtest/gtest.h>
#include <toyjvm/runtime/jvm_thread.h>

namespace jvm_test {
    class InstTestContext : public testing::Test {
    public:
        virtual void SetUp() override
        {
            frame_ = new jvm::JvmFrame(t_, 10, 10);
            opstack_ = &(frame_->operandStack());
        }

        virtual void TearDown() override
        {
            delete frame_;
        }

    protected:
        jvm::bytes bytecode_ = {};
        jvm::JvmThread t_;

        jvm::JvmFrame *frame_;
        jvm::OperandStack *opstack_;
    };
}
#endif //TOYJVM_TEST_INST_CONTEXT_H
