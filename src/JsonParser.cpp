//
// Created by pgkg on 16.11.2020.
//

#include "JsonParser.h"
#include <limits>
#include <sstream>
namespace parser
{

    std::string JsonParser::BooleanToText(const serializer::SBoolean& b) {
        return b.getValue() ? "true" : "false";
    }

    std::string JsonParser::IntToText(const serializer::SInt& i) {
        return std::to_string(i.getValue());
    }

    std::string JsonParser::DoubleToText(const serializer::SDouble& i) {
        return std::to_string(i.getValue());
    }

    std::string JsonParser::StringToText(const serializer::SString& str) {
        return "\"" + str.getValue() + "\"";
    }

    std::string JsonParser::ArrayToText(const serializer::SArray& arr) {
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

    std::string JsonParser::DictToText(const serializer::SDict& dict) {
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

    std::string JsonParser::ObjToText(const serializer::SObj& obj) {
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

    serializer::SObj JsonParser::parseRaw(std::string::const_iterator& it, std::string::const_iterator& it_end) {

        if(*it == 'n')
        {
            it += 4;
            return serializer::SObj(nullptr);
        }else if(*it == 't')
        {
            it += 4;
            return serializer::SBoolean::createBoolean(true);
        }else if(*it == 'f')
        {
            it += 5;
            return serializer::SBoolean::createBoolean(false);
        }
    }

    serializer::SObj JsonParser::parseNum(std::string::const_iterator& it, std::string::const_iterator& it_end) {
        bool isDouble = false;
        auto start = it;
        while(isdigit(*it) || *it == '.' || *it == '-')
        {
            isDouble = (*it == '.' ? true : false);
            it++;
        }
        std::string sub(start.base(), it - start);
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

    serializer::SObj JsonParser::parseString(std::string::const_iterator& it, std::string::const_iterator& it_end) {
        auto start = ++it;
        while((*it != '\"') || (*(it - 1) == '\\'))
        {
            it++;
        }
        std::string sub(start.base(), it - start);
        it++;
        return serializer::SString::createString(sub);
    }

    serializer::SObj JsonParser::parseArray(std::string::const_iterator& it, std::string::const_iterator& it_end) {
        serializer::SArray a = serializer::SArray::createArray();
        while(*it != ']')
        {
            serializer::SObj o = parseObj(it, it_end);
            a.pushBack(o);
            it += *it == ',' ? 2 : 0;
        }
        it++;
        return serializer::SObj(a);
    }

    serializer::SObj JsonParser::parseDict(std::string::const_iterator& it, std::string::const_iterator& it_end) {
        serializer::SDict d = serializer::SDict::createDict();
        while(*it != '}')
        {
            serializer::SString s = parseString(it, it_end);
            it += 2;
            serializer::SObj o = parseObj(it, it_end);
            d.insert(s, o);
            it += *it == ',' ? 2 : 0;
        }
        it++;
        return serializer::SObj(d);
    }

    serializer::SObj JsonParser::parseObj(std::string::const_iterator& it, std::string::const_iterator& it_end) {
        while(it != it_end)
        {
            if(*it == '{')
            {
                return parseDict(++it, it_end);
            }else if(*it == '[')
            {
                return parseArray(++it, it_end);
            }else if(*it == '\"')
            {
                return parseString(it, it_end);
            }else if(isdigit(*it) || *it == '-')
            {
                return parseNum(it, it_end);
            }else if(*it == 't' || *it == 'f' || *it == 'n')
            {
                return parseRaw(it, it_end);
            }else
            {
                throw std::runtime_error("parsing failed");
            }
        }
    }

    serializer::SObj JsonParser::parse(const std::string& str) {
        auto it = str.cbegin();
        auto it_end = str.cend();
        return parseObj(it, it_end);
    }
}