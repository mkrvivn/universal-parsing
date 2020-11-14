//
// Created by pgkg on 14.11.2020.
//

#include "bencode.h"
#include <sstream>
namespace serializer
{
    SDict::SDict(MapPtr val) : _value(val)     {}

    std::string SDict::encode() const {
        if(_cache.empty())
        {
            _cache = cache();
        }
        return _cache;
    }

    std::string SDict::cache() const {
        std::stringstream ss;
        ss << "d";
        for(auto i : *_value)
        {
            ss << i.first->encode();
            ss << i.second.encode();
        }
        ss << "e";
        return ss.str();
    }
}