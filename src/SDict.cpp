//
// Created by pgkg on 14.11.2020.
//

#include "SDict.h"
#include <sstream>
#include <memory>
#include "SObj.h"
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

    void SDict::insert(const SString& s, const SObj& o) {
        _value->insert({s, o});
    }
}