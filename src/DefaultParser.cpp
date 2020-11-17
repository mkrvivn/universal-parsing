//
// Created by pgkg on 17.11.2020.
//
#include "DefaultParser.h"
namespace parser
{
    std::string DefaultParser::BooleanToText(const serializer::SBoolean& b) {
        return "";
    }

    std::string DefaultParser::IntToText(const serializer::SInt& i) {
        return "";
    }

    std::string DefaultParser::DoubleToText(const serializer::SDouble& i) {
        return "";
    }

    std::string DefaultParser::StringToText(const serializer::SString& str) {
        return "";
    }

    std::string DefaultParser::ArrayToText(const serializer::SArray& arr) {
        return "";
    }

    std::string DefaultParser::DictToText(const serializer::SDict& dict) {
        return "";
    }

    std::string DefaultParser::ObjToText(const serializer::SObj& obj) {
        return "";
    }

    std::string DefaultParser::pretty(const serializer::SObj& obj) {
        return "";
    }
}
