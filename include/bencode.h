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
namespace parser
{
    class BencodeParser;
    class JsonParser;
}

namespace serializer
{
    class SInt;
    class SString;
    class SArray;
    class SDict;
    class SObj;
}

namespace parser
{
    struct BencodeParser
    {
        using SelfType = BencodeParser;
        static std::string IntToText(serializer::SInt i);
        static std::string StringToText(serializer::SString str);
        static std::string ArrayToText(serializer::SArray str);
        static std::string DictToText(serializer::SDict str);
        static std::string ObjToText(serializer::SObj obj);
    };
    struct JsonParser
    {
        using SelfType = JsonParser;
        static std::string IntToText(serializer::SInt i);
        static std::string StringToText(serializer::SString str);
        static std::string ArrayToText(serializer::SArray str);
        static std::string DictToText(serializer::SDict str);
        static std::string ObjToText(serializer::SObj obj);
    };
}

namespace serializer
{

    class SValue
    {
    public:
        virtual std::string encode() const = 0;
    };


    typedef std::shared_ptr<SInt> IntPtr;
    typedef std::shared_ptr<SString> StringPtr;
    typedef std::shared_ptr<SArray> ArrayPtr;
    typedef std::shared_ptr<SDict> DictPtr;



    typedef std::variant<SInt, SString, SArray, SDict> SData;

    class SInt
    {
    public:
        SInt(){};
        SInt(int val);
        template<class Parser>
        std::string encode() const;
        operator int() const;
        int getValue() const;
    private:
        int _value;
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
        SObj& operator[](const char* key);
    private:
        MapPtr _value;
    };

    enum class Type
    {
        String,
        Int,
        Array,
        Pair,
        Dict

    };

    typedef std::shared_ptr<SObj> ObjPtr;

    class SObj
    {
    public:
        SObj(){};
        SObj(int val);
        SObj(const char* val);
        SObj(std::initializer_list<SObj> il);
        template<class Parser>
        std::string encode() const;
        SObj& operator[](int pos);
        SObj& operator[](const char* key);
        SData getValue() const;
        operator int() const;
        operator std::string() const;
        operator SInt() const;
        operator SString() const;
        operator SArray() const;
        operator SDict() const;
    private:
        Type _type;
        mutable std::string _cache;
        SData _value;
    private:
        template<class Parser>
        std::string cache() const;
    };

    template<class Parser>
    std::string SInt::encode() const {
        return Parser::IntToText(*this);
    }

    template<class Parser>
    std::string SString::encode() const {
        return Parser::StringToText(*this);
    }

    template<class Parser>
    std::string SDict::encode() const {
        return Parser::DictToText(*this);
    }

    template<class Parser>
    std::string SArray::encode() const {
        return Parser::ArrayToText(*this);
    }

    template<class Parser>
    std::string SObj::cache() const {
        return Parser::ObjToText(*this);
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
