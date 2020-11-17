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

    serializer::SObj BencodeParser::parse(const std::string& str) {
        auto it = str.cbegin();
        auto it_end = str.cend();
        return parseObj(it, it_end);
    }

    serializer::SObj BencodeParser::parseObj(std::string::const_iterator& it, std::string::const_iterator& it_end) {
        while(it != it_end)
        {
            if(*it == 'd')
            {
                return parseDict(++it, it_end);
            }else if(*it == 'l')
            {
                return parseArray(++it, it_end);
            }else if(*it == isdigit(*it))
            {
                return parseString(++it, it_end);
            }else if(*it == 'i')
            {
                return parseInt(++it, it_end);
            }else
            {
                throw std::runtime_error("parsing error");
            }
        }
    }

    serializer::SObj BencodeParser::parseDict(std::string::const_iterator& it, std::string::const_iterator& it_end) {
        serializer::SDict d = serializer::SDict::createDict();
        while(*it != 'e')
        {
            serializer::SString s = parseString(it, it_end);
            serializer::SObj o = parseObj(it, it_end);
            d.insert(s, o);
        }
        it++;
        return serializer::SObj(d);
    }

    serializer::SObj BencodeParser::parseArray(std::string::const_iterator& it, std::string::const_iterator& it_end) {
        serializer::SArray a = serializer::SArray::createArray();
        while(*it != 'e')
        {
            serializer::SObj o = parseObj(it, it_end);
            a.pushBack(o);
        }
        it++;
        return serializer::SObj(a);
    }

    serializer::SObj BencodeParser::parseString(std::string::const_iterator& it, std::string::const_iterator& it_end) {
        auto start = it;
        while(*it != ':')
        {
            it++;
        }
        int len = std::stoi(std::string(start.base(), it - start));
        it++;
        std::string sub(it.base(), len);
        it = it + len;
        return serializer::SString::createString(sub);
    }

    serializer::SObj BencodeParser::parseInt(std::string::const_iterator& it, std::string::const_iterator& it_end) {
        auto start = it;
        while(*it != 'e')
        {
            it++;
        }
        std::string sub(start.base(), it - start); //?????
        it++;
        return serializer::SInt::createInt(std::stoi(sub));
    }
}

