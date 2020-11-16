//
// Created by pgkg on 14.11.2020.
//

#include "bencode.h"
#include <sstream>
#include <algorithm>
#include <iostream>
namespace serializer
{
    //{Sint, Sint}
    //
    SObj::SObj(int val) : _value(std::in_place_type<SInt>, val), _type(Type::Int) {}

    SObj::SObj(const char *val) : _value(std::in_place_type<SString>, val), _type(Type::String) {}

    SObj::SObj(SData val) : _value(val) {}

    SObj::SObj(SInt i) : _value(std::in_place_type<SInt>, i), _type(Type::Int){}

    SObj::SObj(SString s) : _value(std::in_place_type<SString>, s), _type(Type::String) {}

    SObj::SObj(SArray a) : _value(std::in_place_type<SArray>, a), _type(Type::Array) {}

    SObj::SObj(SDict d) : _value(std::in_place_type<SDict>, d), _type(Type::Dict) {}

    SObj::SObj(std::initializer_list<SObj> il) { // <-!!!!!!!!!!!!!!! SObj or ObjPtr???????????
        try {
            if(il.size() == 2 && il.begin()->_type == Type::String)
            {
                VectorPtr arr = std::make_shared<ArrayVector>(il.begin(), il.end());
                _value = SArray(arr); //<--- !!!!!!!!!!!!
                _type = Type::Pair;
                return;
            }else
            {
                bool isDict = std::all_of(il.begin(), il.end(), [](auto&& item){
                    return item._type == Type::Pair;
                });

                if(isDict)
                {
                    MapPtr map = std::make_shared<DictMap>();
                    for(auto i : il)
                    {
                        SArray arr = std::get<SArray>(i._value);
                        map->emplace(std::get<SString>(arr[0]._value), arr[1]); //!!!!!!!!!!!!!!!
                    }
                    _value = SDict(map);
                    _type = Type::Dict;
                }else
                {
                    VectorPtr vec = std::make_shared<ArrayVector>();
                    vec->reserve(il.size());
                    for(auto&& i : il)
                    {
                        vec->emplace_back(i);
                    }
                    _value = SArray(vec);
                    _type = Type::Array;
                }
            }
        } catch (...) {
            std::cout << "something wnt wrong";
        }

    }

    SData SObj::getValue() const {
        return _value;
    }

    SObj& SObj::operator[](int pos) {
        if(_type == Type::Array)
        {
            return std::get<SArray>(_value)[pos];
        }else{
            throw BadType();
        }
    }

    SObj& SObj::operator[](const char* key) {
        if(_type == Type::Dict)
        {
            return std::get<SDict>(_value)[key];
        }else{
            throw BadType();
        }
    }

    SObj::operator int() const
    {
        if(_type == Type::Int){
            return std::get<SInt>(_value);
        }else
        {
            throw BadType();
        }
    }

    SObj::operator std::string() const {
        if(_type == Type::String)
        {
            return std::get<SString>(_value);
        }else
        {
            throw BadType();
        }
    }

    SObj::operator SInt() const {
        if(_type == Type::Int)
        {
            return std::get<SInt>(_value);
        }else
        {
            throw BadType();
        }
    }

    SObj::operator SString() const {
        if(_type == Type::String)
        {
            return std::get<SString>(_value);
        }else
        {
            throw BadType();
        }
    }

    SObj::operator SArray() const {
        if(_type == Type::Array)
        {
            return std::get<SArray>(_value);
        }else
        {
            BadType();
        }
    }

    SObj::operator SDict() const {
        if(_type == Type::Dict)
        {
            return std::get<SDict>(_value);
        }else
        {
            throw BadType();
        }
    }


}