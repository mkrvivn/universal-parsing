//
// Created by pgkg on 17.11.2020.
//

#include "bencode.h"
#include <cmath>
namespace parser
{
    std::string GetRouteParser::BooleanToText(serializer::SBoolean b) {
        return "";
    }

    std::string GetRouteParser::IntToText(serializer::SInt i) {
        return "i" + std::to_string(i.getValue()) + "e";
    }

    std::string GetRouteParser::DoubleToText(serializer::SDouble i) {
        return "i" + std::to_string(floor(i.getValue())) + "e";
    }

    std::string GetRouteParser::StringToText(serializer::SString str) {
        return std::to_string(str.getValue().size()) + ":" + str.getValue();
    }

    std::string GetRouteParser::ArrayToText(serializer::SArray arr) {
        std::stringstream ss;
        ss << "l";
        for(serializer::SObj& i : *arr.getValue())
        {
            ss << i.encode<SelfType>();
        }
        ss << "e";
        return ss.str();
    }

    std::string GetRouteParser::DictToText(serializer::SDict dict) {
        std::stringstream ss;
        ss << "d";
        for(auto& i : *dict.getValue())
        {
            ss << i.first.encode<SelfType>();
            ss << i.second.encode<SelfType>();
        }
        ss << "e";
        return ss.str();
    }

    std::string GetRouteParser::ObjToText(serializer::SObj obj) {
        std::stringstream ss;
        if(obj.getValue().has_value())
        {
            ss << std::visit([](auto&& item){return item.template encode<SelfType>();}, obj.getValue().value());
        }
        return ss.str();
    }

    std::string GetRouteParser::pretty(serializer::SObj obj) {
        return obj.encode<SelfType>();
    }
}