//
// Created by pgkg on 17.11.2020.
//

#ifndef BENCODE_ENCODE_H
#define BENCODE_ENCODE_H
#include "MethodExistenceCheck.h"

#include "SBoolean.h"
#include "SInt.h"
#include "SDouble.h"
#include "SString.h"
#include "SArray.h"
#include "SDict.h"
#include "SObj.h"
#include "DefaultParser.h"

namespace serializer
{
    template <class Parser>
    std::string SBoolean::encode() const {
        if constexpr (is_exist_boolean<Parser, std::string(SBoolean)>::value)
        {
            return Parser::BooleanToText(*this);
        }else
        {
            return parser::DefaultParser::BooleanToText(*this);
        }
    }

    template<class Parser>
    std::string SInt::encode() const {
        if constexpr (is_exist_int<Parser, std::string(SInt)>::value)
        {
            return Parser::IntToText(*this);
        }else
        {
            return parser::DefaultParser::IntToText(*this);
        }
    }

    template<class Parser>
    std::string SDouble::encode() const {
        if constexpr (is_exist_double<Parser, std::string(SDouble)>::value)
        {
            return Parser::DoubleToText(*this);
        }else
        {
            return parser::DefaultParser::DoubleToText(*this);
        }
    }

    template<class Parser>
    std::string SString::encode() const {
        if constexpr (is_exist_string<Parser, std::string(SString)>::value)
        {
            return Parser::StringToText(*this);
        }else
        {
            return parser::DefaultParser::StringToText(*this);
        }
    }

    template<class Parser>
    std::string SDict::encode() const {
        if constexpr (is_exist_dict<Parser, std::string(SDict)>::value)
        {
            return Parser::DictToText(*this);
        }else
        {
            return parser::DefaultParser::DictToText(*this);
        }
    }

    template<class Parser>
    std::string SArray::encode() const {
        if constexpr (is_exist_array<Parser, std::string(SArray)>::value)
        {
            return Parser::ArrayToText(*this);
        }else
        {
            return parser::DefaultParser::ArrayToText(*this);
        }
    }

    template<class Parser>
    std::string SObj::cache() const {
        if constexpr (is_exist_obj<Parser, std::string(SObj)>::value)
        {
            return Parser::ObjToText(*this);
        }else
        {
            return parser::DefaultParser::ObjToText(*this);
        }
    }

    template<class Parser>
    std::string SObj::encode() const {
        if(_cache.empty())
        {
            _cache = cache<Parser>();
        }
        return _cache;
    }
}

#endif //BENCODE_ENCODE_H
