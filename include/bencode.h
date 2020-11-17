//
// Created by pgkg on 14.11.2020.
//

#ifndef BENCODE_BENCODE_H
#define BENCODE_BENCODE_H
#include <variant>
#include <memory>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <iostream>
#include "exception.h"
#include <sstream>
#include <string>
#include <optional>
#include "MethodExistenceCheck.h"
#include <type_traits>
namespace parser
{
    class BencodeParser;
    class JsonParser;
}

namespace serializer
{
    class SBoolean;
    class SInt;
    class SDouble;
    class SString;
    class SArray;
    class SDict;
    class SObj;
}

namespace parser
{
    struct DefaultParser
    {
        using SelfType = DefaultParser;
        static std::string NullToText();
        static std::string BooleanToText(serializer::SBoolean b);
        static std::string IntToText(serializer::SInt i);
        static std::string DoubleToText(serializer::SDouble d);
        static std::string StringToText(serializer::SString str);
        static std::string ArrayToText(serializer::SArray str);
        static std::string DictToText(serializer::SDict str);
        static std::string ObjToText(serializer::SObj obj);
        static std::string pretty(serializer::SObj obj);
    };
    struct BencodeParser
    {
        using SelfType = BencodeParser;
        static std::string NullToText();
        static std::string BooleanToText(serializer::SBoolean b);
        static std::string IntToText(serializer::SInt i);
        static std::string DoubleToText(serializer::SDouble d);
        static std::string StringToText(serializer::SString str);
        static std::string ArrayToText(serializer::SArray str);
        static std::string DictToText(serializer::SDict str);
        static std::string ObjToText(serializer::SObj obj);
        static std::string pretty(serializer::SObj obj);
        static serializer::SObj parse(char*& ptr);
    private:
        static serializer::SObj parseDict(char*& ptr);
        static serializer::SObj parseArray(char*& ptr);
        static serializer::SObj parseString(char*& ptr);
        static serializer::SObj parseInt(char*& ptr);
    };
    struct JsonParser
    {
        using SelfType = JsonParser;
        static std::string NullToText();
        static std::string BooleanToText(serializer::SBoolean b);
        static std::string IntToText(serializer::SInt i);
        static std::string DoubleToText(serializer::SDouble d);
        static std::string StringToText(serializer::SString str);
        static std::string ArrayToText(serializer::SArray str);
        static std::string DictToText(serializer::SDict str);
        static std::string ObjToText(serializer::SObj obj);
        static std::string pretty(serializer::SObj obj);
        static serializer::SObj parse(char*& ptr);
    private:
        static serializer::SObj parseDict(char*& ptr);
        static serializer::SObj parseArray(char*& ptr);
        static serializer::SObj parseString(char*& ptr);
        static serializer::SObj parseNum(char*& ptr);
        static serializer::SObj parseRaw(char*& ptr);
    };
    struct GetRouteParser
    {
        using SelfType = GetRouteParser;
        static std::string NullToText();
        static std::string BooleanToText(serializer::SBoolean b);
        static std::string IntToText(serializer::SInt i);
        static std::string DoubleToText(serializer::SDouble d);
        static std::string StringToText(serializer::SString str);
        static std::string ArrayToText(serializer::SArray str);
        static std::string DictToText(serializer::SDict str);
        static std::string ObjToText(serializer::SObj obj);
        static std::string pretty(serializer::SObj obj);
        static serializer::SObj parse(char*& schema, char*& ptr);
    private:
        static serializer::SObj parseDict(char*& ptr);
        static serializer::SObj parseArray(char*& ptr);
        static serializer::SObj parseString(char*& ptr);
        static serializer::SObj parseNum(char*& ptr);
        static serializer::SObj parseRaw(char*& ptr);
    };
}

namespace serializer
{

    typedef std::variant<SBoolean, SInt, SDouble, SString, SArray, SDict> SData;
    typedef std::optional<SData> SDataOpt;
    class SInt
    {
    public:
        SInt(){};
        SInt(int val);
        template<class Parser>
        std::string encode() const;
        operator int() const;
        int getValue() const;
        static SInt createInt(int);
    private:
        int _value;
    };

    class SDouble
    {
    public:
        SDouble(){};
        SDouble(double val);
        template<class Parser>
        std::string encode() const;
        operator double () const;
        double getValue() const;
        static SDouble createDouble(double);
    private:
        double _value;
    };

    class SBoolean
    {
    public:
        SBoolean(){};
        SBoolean(bool val);
        template<class Parser>
        std::string encode() const;
        operator bool() const;
        bool getValue() const;
        static SBoolean createBoolean(bool);
    private:
        bool _value;
    };

    class SString
    {
    public:
        SString(){};
        SString(std::string val);
        template<class Parser>
        std::string encode() const;
        operator std::string() const;
        std::string& getValue() const;
        bool operator==(const SString& rhs) const
        {
            return *_value == *rhs._value;
        }
        static SString createString(std::string);
        struct hash{
            size_t operator()(const SString& val) const {
                return std::hash<std::string>()(*val._value);
            }
        };
    private:
        std::shared_ptr<std::string> _value;
    };

    typedef std::vector<SObj> ArrayVector;
    typedef std::unordered_map<SString, SObj, SString::hash> DictMap;

    typedef std::shared_ptr<ArrayVector> VectorPtr;
    typedef std::shared_ptr<DictMap> MapPtr;

    class SArray
    {
    public:
        SArray(){};
        SArray(std::shared_ptr<std::vector<SObj>> val);
        template<class Parser>
        std::string encode() const;
        VectorPtr getValue() const;
        SObj& operator[](int pos);
        void pushBack(SObj);
        static SArray createArray();
    private:
        VectorPtr _value;
    };

    class SDict
    {
    public:
        SDict(){};
        SDict(MapPtr val);
        template<class Parser>
        std::string encode() const;
        MapPtr getValue() const;
        void insert(SString, SObj);
        SObj& operator[](const char* key);
        static SDict createDict();
    private:
        MapPtr _value;
    };

    enum class Type
    {
        Null,
        Boolean,
        Int,
        Double,
        String,
        Array,
        Pair,
        Dict

    };

    class SObj
    {
    public:
        SObj(){};
        SObj(int val);
        SObj(double val);
        SObj(const char* val);
        SObj(SData val);
        SObj(SBoolean);
        SObj(SInt i);
        SObj(SDouble d);
        SObj(SString s);
        SObj(SArray a);
        SObj(SDict d);
        SObj(std::initializer_list<SObj> il);
        template<class Parser>
        std::string encode() const;
        SObj& operator[](int pos);
        SObj& operator[](const char* key);
        SDataOpt getValue() const;
        operator void*() const;
        operator bool() const;
        operator int() const;
        operator double() const;
        operator std::string() const;
        operator SBoolean() const;
        operator SInt() const;
        operator SDouble() const;
        operator SString() const;
        operator SArray() const;
        operator SDict() const;
    private:
        Type _type;
        mutable std::string _cache;
        std::optional<SData> _value;
    private:
        template<class Parser>
        std::string cache() const;
    };

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




#endif //BENCODE_BENCODE_H
