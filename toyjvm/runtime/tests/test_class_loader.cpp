//
// Created by cyhone on 18-4-29.
//

#include <gtest/gtest.h>
#include <toyjvm/runtime/class_loader.h>
#include <toyjvm/runtime/jvm_class.h>

using namespace jvm;

TEST(test_class_loader, normal)
{
    Loader::instance()->init("", "");
    auto strClass = Loader::instance()->loadNonArrayClass("java/lang/String");

    EXPECT_EQ("Ljava/lang/String;", strClass->descriptor());
}