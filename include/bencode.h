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
#include "move_wrapper.h"
#include "exception.h"
namespace serializer
{

    class SValue
    {
    public:
        virtual std::string encode() const = 0;
    };

    class SInt;
    class SString;
    class SArray;
    class SDict;
    class SObj;

    typedef std::shared_ptr<SInt> IntPtr;
    typedef std::shared_ptr<SString> StringPtr;
    typedef std::shared_ptr<SArray> ArrayPtr;
    typedef std::shared_ptr<SDict> DictPtr;



    typedef std::variant<SInt, SString, SArray, SDict> SData;

    class SInt
    {
    public:
        ~SInt(){std::cout << "int delited" << std::endl;}
        SInt(){};
        SInt(int val);
        std::string encode() const;
        operator int() const;
        int getValue();
    private:
        int _value;
    };

    class SString
    {
    public:
        ~SString(){std::cout << "string delited" << std::endl;}
        SString(){};
        SString(std::string val);
        std::string encode() const;
        operator std::string() const;
        std::string getValue();
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
        std::string encode() const;
        SObj& operator[](int pos);
    private:
        VectorPtr _value;
    };

    class SDict
    {
    public:
        SDict(){};
        SDict(MapPtr val);
        std::string encode() const;
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
        std::string encode() const;
        SObj& operator[](int pos);
        SObj& operator[](const char* key);
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
        std::string cache() const;
    };

}


namespace parser
{

}
#endif //BENCODE_BENCODE_H
