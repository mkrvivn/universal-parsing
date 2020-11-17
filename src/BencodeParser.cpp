//
// Created by pgkg on 16.11.2020.
//
#include "bencode.h"
#include <cmath>
namespace parser
{
    std::string BencodeParser::BooleanToText(serializer::SBoolean b) {
        return "";
    }

    std::string BencodeParser::IntToText(serializer::SInt i) {
        return "i" + std::to_string(i.getValue()) + "e";
    }

    std::string BencodeParser::DoubleToText(serializer::SDouble i) {
        return "i" + std::to_string(floor(i.getValue())) + "e";
    }

    std::string BencodeParser::StringToText(serializer::SString str) {
        return std::to_string(str.getValue().size()) + ":" + str.getValue();
    }

    std::string BencodeParser::ArrayToText(serializer::SArray arr) {
        std::stringstream ss;
        ss << "l";
        for(serializer::SObj& i : *arr.getValue())
        {
            ss << i.encode<SelfType>();
        }
        ss << "e";
        return ss.str();
    }

    std::string BencodeParser::DictToText(serializer::SDict dict) {
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

    std::string BencodeParser::ObjToText(serializer::SObj obj) {
        std::stringstream ss;
        if(obj.getValue().has_value())
        {
            ss << std::visit([](auto&& item){return item.template encode<SelfType>();}, obj.getValue().value());
        }


        return ss.str();
    }

    std::string BencodeParser::pretty(serializer::SObj obj) {
        return obj.encode<SelfType>();
    }

    serializer::SObj BencodeParser::parse(char*& ptr) {
        while(*ptr != '\0')
        {
            if(*ptr == 'd')
            {
                return parseDict(++ptr);
            }else if(*ptr == 'l')
            {
                return parseArray(++ptr);
            }else if(*ptr == isdigit(*ptr))
            {
                return parseString(++ptr);
            }else if(*ptr == 'i')
            {
                return parseInt(++ptr);
            }else
            {
                throw std::runtime_error("parsing error");
            }
        }
    }

    serializer::SObj BencodeParser::parseDict(char*& ptr) {
        serializer::SDict d = serializer::SDict::createDict();
        while(*ptr != 'e')
        {
            serializer::SString s = parseString(ptr);
            serializer::SObj o = parse(ptr);
            d.insert(s, o);
        }
        ptr++;
        return serializer::SObj(d);
    }

    serializer::SObj BencodeParser::parseArray(char*& ptr) {
        serializer::SArray a = serializer::SArray::createArray();
        while(*ptr != 'e')
        {
            serializer::SObj o = parse(ptr);
            a.pushBack(o);
        }
        ptr++;
        return serializer::SObj(a);
    }

    serializer::SObj BencodeParser::parseString(char*& ptr) {
        auto start = ptr;
        while(*ptr != ':')
        {
            ptr++;
        }
        int len = std::stoi(std::string(start, ptr - start));
        ptr++;
        std::string sub(ptr, len);
        ptr = ptr + len;
        return serializer::SString::createString(sub);
    }

    serializer::SObj BencodeParser::parseInt(char*& ptr) {
        auto start = ptr;
        while(*ptr != 'e')
        {
            ptr++;
        }
        std::string sub(start, ptr - start); //?????
        ptr++;
        return serializer::SInt::createInt(std::stoi(sub));
    }
}

