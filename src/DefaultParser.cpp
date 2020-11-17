//
// Created by pgkg on 17.11.2020.
//
#include "bencode.h"
#include <cmath>
namespace parser
{
    std::string DefaultParser::BooleanToText(serializer::SBoolean b) {
        return "";
    }

    std::string DefaultParser::IntToText(serializer::SInt i) {
        return "";
    }

    std::string DefaultParser::DoubleToText(serializer::SDouble i) {
        return "";
    }

    std::string DefaultParser::StringToText(serializer::SString str) {
        return "";
    }

    std::string DefaultParser::ArrayToText(serializer::SArray arr) {
        return "";
    }

    std::string DefaultParser::DictToText(serializer::SDict dict) {
        return "";
    }

    std::string DefaultParser::ObjToText(serializer::SObj obj) {
        return "";
    }

    std::string DefaultParser::pretty(serializer::SObj obj) {
        return "";
    }
}
