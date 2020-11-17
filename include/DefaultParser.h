//
// Created by pgkg on 17.11.2020.
//

#ifndef BENCODE_DEFAULTPARSER_H
#define BENCODE_DEFAULTPARSER_H
#include <string>
#include "SBoolean.h"
#include "SInt.h"
#include "SDouble.h"
#include "SString.h"
#include "SArray.h"
#include "SDict.h"
#include "SObj.h"
namespace parser
{
    struct DefaultParser
    {
        using SelfType = DefaultParser;
        static std::string NullToText();
        static std::string BooleanToText(const serializer::SBoolean& b);
        static std::string IntToText(const serializer::SInt& i);
        static std::string DoubleToText(const serializer::SDouble& d);
        static std::string StringToText(const serializer::SString& str);
        static std::string ArrayToText(const serializer::SArray& str);
        static std::string DictToText(const serializer::SDict& str);
        static std::string ObjToText(const serializer::SObj& obj);
        static std::string pretty(const serializer::SObj& obj);
    };
}
#endif //BENCODE_DEFAULTPARSER_H
