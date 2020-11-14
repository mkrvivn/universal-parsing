//
// Created by pgkg on 14.11.2020.
//

#include "bencode.h"
#include <sstream>
#include <algorithm>
#include <iostream>
namespace serializer
{
    SObj::SObj(int val) : _value(std::in_place_type<IntPtr>, std::make_shared<SInt>(val)), _type(Type::Int) {}

    SObj::SObj(const char *val) : _value(std::in_place_type<StringPtr>, std::make_shared<SString>(val)), _type(Type::String) {}

    SObj::SObj(std::initializer_list<SObj> il) { // <-!!!!!!!!!!!!!!! SObj or ObjPtr???????????
        if(il.size() == 2 && il.begin()->_type == Type::String)
        {
            VectorPtr arr = std::make_shared<ArrayVector>(il.begin(), il.end());
            _value = std::make_shared<SArray>(arr); //<--- !!!!!!!!!!!!
            _type = Type::Pair;
            return;
        }else
        {
            bool isDict = std::all_of(il.begin(), il.end(), [](SObj item){
                return item._type == Type::Pair;
            });

            if(isDict)
            {
                MapPtr map = std::make_shared<DictMap>();
                for(auto i : il)
                {
                    try {
                        ArrayPtr arr = std::get<ArrayPtr>(i._value);
                        if(arr == nullptr)
                        {
                            throw std::runtime_error("wrong time");
                        }
                        map->emplace(std::get<StringPtr>((*arr)[0]._value), (*arr)[1]); //!!!!!!!!!!!!!!!
                    } catch (...) {
                        std::cout << "wrong type";
                        exit(0);
                    }
                }
                _value = std::make_shared<SDict>(map);
                _type = Type::Dict;
            }else
            {
                VectorPtr vec = std::make_shared<ArrayVector>();
                for(auto i : il)
                {
                    vec->push_back(i);
                }
                _value = std::make_shared<SArray>(vec);
                _type = Type::Array;
            }
            _type = Type::Array;
        }
    }

    std::string SObj::cache() const {
        std::stringstream ss;
        ss << std::visit([](auto&& item){return item->encode();}, _value);
        return ss.str();
    }

    std::string SObj::encode() const {
        if(_cache.empty())
        {
            _cache = cache();
        }
        return _cache;
    }
}