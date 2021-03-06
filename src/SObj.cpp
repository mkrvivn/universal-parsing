//
// Created by pgkg on 14.11.2020.
//

#include "SObj.h"
#include <algorithm>
#include <iostream>
#include "Exceptions.h"
namespace serializer
{
    SObj::SObj() : _type(Type::Null) {}
    
    SObj::SObj(bool val) : _value(std::in_place, std::in_place_type<SBoolean>, val), _type(Type::Boolean) {}

    SObj::SObj(int val) : _value(std::in_place, std::in_place_type<SInt>, val), _type(Type::Int) {}

    SObj::SObj(const char *val) {
        if(val != nullptr)
        {
            _value = SData(std::in_place_type<SString>, val);
            _type = Type::String;
        }else
        {
            _type = Type::Null;
        }
    }

    SObj::SObj(double val) : _value(std::in_place, std::in_place_type<SDouble>, val), _type(Type::Double){}

    SObj::SObj(SInt i) : _value(std::in_place, std::in_place_type<SInt>, i), _type(Type::Int){}

    SObj::SObj(SDouble d) : _value(std::in_place, std::in_place_type<SDouble>, d), _type(Type::Double){}

    SObj::SObj(SBoolean b) : _value(b), _type(Type::Boolean) {}

    SObj::SObj(SString s) : _value(std::in_place, std::in_place_type<SString>, s), _type(Type::String) {}

    SObj::SObj(SArray a) : _value(std::in_place, std::in_place_type<SArray>, a), _type(Type::Array) {}

    SObj::SObj(SDict d) : _value(std::in_place, std::in_place_type<SDict>, d), _type(Type::Dict) {}

    SObj::SObj(std::initializer_list<SObj> il) {
            if(il.size() == 2 && il.begin()->_type == Type::String)
            {
                _value = SArray(std::make_shared<ArrayVector>(il.begin(), il.end())); //<--- !!!!!!!!!!!!
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
                        SArray arr = std::get<SArray>(i._value.value());
                        map->emplace(std::get<SString>(arr[0]._value.value()), arr[1]); //!!!!!!!!!!!!!!!
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
    }

    SDataOpt SObj::getValue() const {
        return _value;
    }

    SObj& SObj::operator[](int pos) {
        if(_type == Type::Array)
        {
            return std::get<SArray>(_value.value())[pos];
        }else{
            throw serializer::exceptions::BadType();
        }
    }

    SObj& SObj::operator[](const char* key) {
        if(_type == Type::Dict)
        {
            return std::get<SDict>(_value.value())[key];
        }else{
            throw serializer::exceptions::BadType();
        }
    }

    SObj::operator void *() const {
        if(_type == Type::Null)
        {
            return nullptr;
        }else
        {
            throw serializer::exceptions::BadType();
        }
    }

    SObj::operator bool() const {
        if(_type == Type::Boolean){
            return std::get<SBoolean>(_value.value()).getValue();
        }else
        {
            throw serializer::exceptions::BadType();
        }
    }

    SObj::operator int() const
    {
        if(_type == Type::Int){
            return std::get<SInt>(_value.value()).getValue();
        }else
        {
            throw serializer::exceptions::BadType();
        }
    }

    SObj::operator double() const {
        if(_type == Type::Double)
        {
            return std::get<SDouble>(_value.value()).getValue();
        }else
        {
            throw serializer::exceptions::BadType();
        }
    }

    SObj::operator std::string() const {
        if(_type == Type::String)
        {
            return std::get<SString>(_value.value());
        }else
        {
            throw serializer::exceptions::BadType();
        }
    }

    SObj::operator SBoolean() const {
        if(_type == Type::Boolean)
        {
            return std::get<SBoolean>(_value.value());
        }else
        {
            throw serializer::exceptions::BadType();
        }

    }

    SObj::operator SInt() const {
        if(_type == Type::Int)
        {
            return std::get<SInt>(_value.value());
        }else
        {
            throw serializer::exceptions::BadType();
        }
    }

    SObj::operator SDouble() const {
        if(_type == Type::Double)
        {
            return std::get<SDouble>(_value.value());
        }else
        {
            throw serializer::exceptions::BadType();
        }
    }



    SObj::operator SString() const {
        if(_type == Type::String)
        {
            return std::get<SString>(_value.value());
        }else
        {
            throw serializer::exceptions::BadType();
        }
    }

    SObj::operator SArray() const {
        if(_type == Type::Array)
        {
            return std::get<SArray>(_value.value());
        }else
        {
            throw serializer::exceptions::BadType();
        }
    }

    SObj::operator SDict() const {
        if(_type == Type::Dict)
        {
            return std::get<SDict>(_value.value());
        }else
        {
            throw serializer::exceptions::BadType();
        }
    }


}