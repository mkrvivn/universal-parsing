//
// Created by pgkg on 18.11.2020.
//
#include "gtest/gtest.h"
#include <iostream>
#include "Serializer.h"
#include "BencodeParser.h"

TEST(BencodeParserTest, SimpleTest) {
std::string bencode = "d3:bar4:spam3:fooi42ee";
auto o = parser::BencodeParser::parse(bencode);
ASSERT_EQ(o.encode<parser::BencodeParser>(), "d3:bar4:spam3:fooi42ee");
}

TEST(BencodeParserTest, ComplexTest) {
    std::string bencode = "d4:dictd11:dict-item-14:test11:dict-item-25:thinge4:listl11:list-item-111:list-item-2e6:numberi123456e6:string5:valuee";
    auto o = parser::BencodeParser::parse(bencode);
    ASSERT_EQ(o.encode<parser::BencodeParser>(), bencode);
}
