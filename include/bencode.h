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
#include <iostream>
#include "move_wrapper.h"
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

    typedef std::vector<SObj> ArrayVector;
    typedef std::map<StringPtr, SObj> DictMap;

    typedef std::shared_ptr<ArrayVector> VectorPtr;
    typedef std::shared_ptr<DictMap> MapPtr;



    typedef std::variant<IntPtr, StringPtr, ArrayPtr, DictPtr> SData;

    class SInt
    {
    public:
        ~SInt() {std::cout << "deleted int" << std::endl;}
        SInt(int val);
        std::string encode() const;
    private:
        mutable std::string _cache;
        int _value;
    private:
        std::string cache() const;
    };

    class SString
    {
    public:
        ~SString() {std::cout << "deleted string" << std::endl;}
        SString(std::string val);
        std::string encode() const;
        bool operator<(const SString& rhs) const
        {
            return _value < rhs._value;
        }
    private:
        mutable std::string _cache;
        std::string _value;
    private:
        std::string cache() const;
    };

    class SArray
    {
    public:
        SArray(std::shared_ptr<std::vector<SObj>> val);
        std::string encode() const;
        SObj operator[](int pos);
    private:
        mutable std::string _cache;
        VectorPtr _value;
    private:
        std::string cache() const;
    };

    class SDict
    {
    public:
        SDict(MapPtr val);
        std::string encode() const;
    private:
        mutable std::string _cache;
        MapPtr _value;
    private:
        std::string cache() const;
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
    class SObj : public SValue
    {
    public:
        SObj(int val);
        SObj(const char* val);
        SObj(std::initializer_list<SObj> il);
        std::string encode() const override;
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
