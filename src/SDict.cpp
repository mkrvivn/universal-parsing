//
// Created by pgkg on 14.11.2020.
//

#include "bencode.h"
#include <sstream>
namespace serializer
{
    SDict::SDict(MapPtr val) : _value(std::move(val))     {}

    SObj & SDict::operator[](const char* key) {
        return _value->operator[](std::string(key));
    }

    MapPtr SDict::getValue() const {
        return _value;
    }
}