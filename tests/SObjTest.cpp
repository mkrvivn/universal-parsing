//
// Created by pgkg on 18.11.2020.
//
#include "gtest/gtest.h"
#include <iostream>
#include "Serializer.h"
TEST(SObjTest, TypeConversationTest)
{
    serializer::SObj o = nullptr;
    void* test_null = o;
    ASSERT_EQ(test_null, nullptr) << "null conversation error";

    o = true;
    bool test_bool = o;
    ASSERT_EQ(true, true) << "bool conversation error";

    o = 1;
    int test_int = o;
    ASSERT_EQ(test_int, 1) << "int conversation error";

    o = 3.1415;
    double test_double = o;
    ASSERT_EQ(test_double, 3.1415) << "double conversation error";

    o = "string";
    std::string test_string = o;
    ASSERT_EQ(test_string, "string") << "string conversation error";

}

GTEST_API_ int main(int argc, char **argv) {
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}