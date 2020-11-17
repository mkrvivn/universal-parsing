//
// Created by pgkg on 17.11.2020.
//

#ifndef BENCODE_JSONPARSER_H
#define BENCODE_JSONPARSER_H
#include <string>
#include "Encode.h"
namespace parser
{
    struct JsonParser
    {
        using SelfType = JsonParser;
        static std::string NullToText();
        static std::string BooleanToText(const serializer::SBoolean& b);
        static std::string IntToText(const serializer::SInt& i);
        static std::string DoubleToText(const serializer::SDouble& d);
        static std::string StringToText(const serializer::SString& str);
        static std::string ArrayToText(const serializer::SArray& str);
        static std::string DictToText(const serializer::SDict& str);
        static std::string ObjToText(const serializer::SObj& obj);
        static serializer::SObj parse(const std::string & str);
    private:
        static serializer::SObj parseObj(std::string::const_iterator& it, std::string::const_iterator& it_end);
        static serializer::SObj parseDict(std::string::const_iterator& it, std::string::const_iterator& it_end);
        static serializer::SObj parseArray(std::string::const_iterator& it, std::string::const_iterator& it_end);
        static serializer::SObj parseString(std::string::const_iterator& it, std::string::const_iterator& it_end);
        static serializer::SObj parseNum(std::string::const_iterator& it, std::string::const_iterator& it_end);
        static serializer::SObj parseRaw(std::string::const_iterator& it, std::string::const_iterator& it_end);
    };
}
#endif //BENCODE_JSONPARSER_H
