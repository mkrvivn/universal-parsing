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

    SDict SDict::createDict() {
        return SDict(std::make_shared<DictMap>());
    }

    void SDict::insert(SString s, SObj o) {
        _value->insert({s, o});
    }
}