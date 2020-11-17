//
// Created by pgkg on 16.11.2020.
//

#include "bencode.h"
#include <limits>
namespace parser
{
    std::string JsonParser::BooleanToText(serializer::SBoolean b) {
        return b.getValue() ? "true" : "false";
    }

    std::string JsonParser::IntToText(serializer::SInt i) {
        return std::to_string(i.getValue());
    }

    std::string JsonParser::DoubleToText(serializer::SDouble i) {
        return std::to_string(i.getValue());
    }

    std::string JsonParser::StringToText(serializer::SString str) {
        return "\"" + str.getValue() + "\"";
    }

    std::string JsonParser::ArrayToText(serializer::SArray arr) {
        std::stringstream ss;
        ss << "[";
        auto end = arr.getValue()->end();
        for(auto it = arr.getValue()->begin(); it != end; it++)
        {
            if(std::next(it) != end)
            {
                ss << it->encode<SelfType>();
                ss << ", ";
            }else
            {
                ss << it->encode<SelfType>();
            }
        }
        ss << "]";
        return ss.str();
    }

    std::string JsonParser::DictToText(serializer::SDict dict) {
        std::stringstream ss;
        ss << "{";
        auto end = dict.getValue()->end();
        for(auto it = dict.getValue()->begin(); it != end; it++)
        {
            if(std::next(it) != end)
            {
                ss << it->first.encode<SelfType>();
                ss << ": ";
                ss << it->second.encode<SelfType>();
                ss << ", ";
            } else
            {
                ss << it->first.encode<SelfType>();
                ss << ": ";
                ss << it->second.encode<SelfType>();
            }
        }
        ss << "}";
        return ss.str();
    }

    std::string JsonParser::ObjToText(serializer::SObj obj) {
        std::stringstream ss;
        if(obj.getValue().has_value())
        {
            ss << std::visit([](auto&& item){return item.template encode<SelfType>();}, obj.getValue().value());
        }else
        {
            ss << "null";
        }
        return ss.str();
    }

    serializer::SObj JsonParser::parseRaw(char *&ptr) {

        if(*ptr == 'n')
        {
            ptr += 4;
            return serializer::SObj(nullptr);
        }else if(*ptr == 't')
        {
            ptr += 4;
            return serializer::SBoolean::createBoolean(true);
        }else if(*ptr == 'f')
        {
            ptr += 5;
            return serializer::SBoolean::createBoolean(false);
        }
    }

    serializer::SObj JsonParser::parseNum(char *&ptr) {
        bool isDouble = false;
        auto start = ptr;
        while(isdigit(*ptr) || *ptr == '.' || *ptr == '-')
        {
            isDouble = (*ptr == '.' ? true : false);
            ptr++;
        }
        std::string sub(start, ptr - start);
        if(isDouble)
        {
            return serializer::SDouble::createDouble(std::stod(sub));
        }else
        {
            int tmp;
            try {
                tmp = std::stoi(sub);
            } catch (...) {
                tmp = std::numeric_limits<int>::max();
            }
            return serializer::SInt::createInt(tmp);
        }
    }

    serializer::SObj JsonParser::parseString(char *&ptr) {
        auto start = ++ptr;
        while((*ptr != '\"') || (*(ptr - 1) == '\\'))
        {
            ptr++;
        }
        std::string sub(start, ptr - start);
        ptr++;
        return serializer::SString::createString(sub);
    }

    serializer::SObj JsonParser::parseArray(char *&ptr) {
        serializer::SArray a = serializer::SArray::createArray();
        while(*ptr != ']')
        {
            serializer::SObj o = parse(ptr);
            a.pushBack(o);
            ptr += *ptr == ',' ? 2 : 0;
        }
        ptr++;
        return serializer::SObj(a);
    }

    serializer::SObj JsonParser::parseDict(char *&ptr) {
        serializer::SDict d = serializer::SDict::createDict();
        while(*ptr != '}')
        {
            serializer::SString s = parseString(ptr);
            ptr += 2;
            serializer::SObj o = parse(ptr);
            d.insert(s, o);
            ptr += *ptr == ',' ? 2 : 0;
        }
        ptr++;
        return serializer::SObj(d);
    }

    serializer::SObj JsonParser::parse(char *&ptr) {
        while(*ptr != '\0')
        {
            if(*ptr == '{')
            {
                return parseDict(++ptr);
            }else if(*ptr == '[')
            {
                return parseArray(++ptr);
            }else if(*ptr == '\"')
            {
                return parseString(ptr);
            }else if(isdigit(*ptr) || *ptr == '-')
            {
                return parseNum(ptr);
            }else if(*ptr == 't' || *ptr == 'f' || *ptr == 'n')
            {
                return parseRaw(ptr);
            }else
            {
                throw std::runtime_error("parsing failed");
            }
        }
    }
}