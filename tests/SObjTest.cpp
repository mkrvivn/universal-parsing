//
// Created by pgkg on 18.11.2020.
//
#include "gtest/gtest.h"
#include <iostream>
#include "Serializer.h"
TEST(SObjTest, TypeConversationTestNull) {
    serializer::SObj o = nullptr;
    void *test_null = o;
    ASSERT_EQ(test_null, nullptr);
}

TEST(SObjTest, TypeConversationTestBool) {
    serializer::SObj o = nullptr;
    o = true;
    bool test_bool = o;
    ASSERT_EQ(true, true);
}

TEST(SObjTest, TypeConversationTestInt) {
    serializer::SObj o = nullptr;
    o = 1;
    int test_int = o;
    ASSERT_EQ(test_int, 1);
}

TEST(SObjTest, TypeConversationTestDouble) {
    serializer::SObj o = nullptr;
    o = 3.1415;
    double test_double = o;
    ASSERT_EQ(test_double, 3.1415);
}

TEST(SObjTest, TypeConversationTestString) {
    serializer::SObj o = nullptr;
    o = "string";
    std::string test_string = o;
    ASSERT_EQ(test_string, "string");
}

TEST(SObjTest, TypeConversationTestArray) {
    serializer::SObj o = nullptr;
    o = {1, 2, 3, 4, 5};
    int test_assign = o[3];
    ASSERT_EQ(test_assign, 4);
}

TEST(SObjTest, TypeConversationTestDict) {
    serializer::SObj o = nullptr;
    o = {{"a", 1}, {"b", 2}};
    int test_dict = o["a"];
    ASSERT_EQ(test_dict, 1);
}

TEST(SObjTest, InsertionTest) {
    serializer::SObj o = nullptr;
    o = {{"a", 1}, {"b", 2}};
    o["arr"] = {1, 2, 3, 4, 5};
    int test_dict = o["arr"][3];
    ASSERT_EQ(test_dict, 4);
}

TEST(SObjTest, EditTest) {
    serializer::SObj o = nullptr;
    o = {{"a", 1}, {"b", 2}};
    o["a"] = {1, 2, 3, 4, 5};
    int test_dict = o["a"][3];
    ASSERT_EQ(test_dict, 4);
}


GTEST_API_ int main(int argc, char **argv) {
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}