//
// Created by pgkg on 14.11.2020.
//

#include "bencode.h"
#include <sstream>
namespace serializer
{
    SDict::SDict(MapPtr val) : _value(std::move(val))     {}

    std::string SDict::encode() const {
        std::stringstream ss;
        ss << "d";
        for(auto& i : *_value)
        {
            ss << i.first.encode();
            ss << i.second.encode();
        }
        ss << "e";
        return ss.str();
    }

    SObj & SDict::operator[](const char* key) {
        std::cout << "input string: "<< SString(key).encode() << std::endl;
        if(_value->contains(SString(key)))
        {
            std::cout << "contains" << std::endl;
        }
        return _value->operator[](std::string(key));
    }

}