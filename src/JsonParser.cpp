//
// Created by pgkg on 16.11.2020.
//

#include "bencode.h"
namespace parser
{
    std::string JsonParser::IntToText(serializer::SInt i) {
        return "!i!" + std::to_string(i.getValue()) + "e";
    }

    std::string JsonParser::StringToText(serializer::SString str) {
        return std::to_string(str.getValue().size()) + "!:!" + str.getValue();
    }

    std::string JsonParser::ArrayToText(serializer::SArray arr) {
        std::stringstream ss;
        ss << "!l!";
        for(serializer::SObj& i : *arr.getValue())
        {
            ss << i.encode<SelfType>();
        }
        ss << "e";
        return ss.str();
    }

    std::string JsonParser::DictToText(serializer::SDict dict) {
        std::stringstream ss;
        ss << "!d!";
        for(auto& i : *dict.getValue())
        {
            ss << i.first.encode<SelfType>();
            ss << i.second.encode<SelfType>();
        }
        ss << "e";
        return ss.str();
    }

    std::string JsonParser::ObjToText(serializer::SObj obj) {
        std::stringstream ss;
        ss << std::visit([](auto&& item){return item.template encode<SelfType>();}, obj.getValue());
        return ss.str();
    }
}