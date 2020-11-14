//
// Created by pgkg on 14.11.2020.
//

#include "bencode.h"
#include <sstream>
namespace serializer
{
    std::string SString::encode() const {
        if(_cache.empty())
        {
            _cache = cache();
        }
        return _cache;
    }

    std::string SString::cache() const {
        std::stringstream ss;
        ss << std::to_string(_value.size()) << ":" << _value;
        return ss.str();
    }

    SString::SString(std::string val): _value(val) {}
}