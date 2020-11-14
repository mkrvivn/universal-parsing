//
// Created by pgkg on 14.11.2020.
//

#include "bencode.h"
#include <sstream>
namespace serializer
{
    std::string SInt::encode() const {
        if(_cache.empty())
        {
            _cache = cache();
        }
        return _cache;
    }

    std::string SInt::cache() const{
        std::stringstream ss;
        ss << "i" << std::to_string(_value) << "e";
        return ss.str();
    }

    SInt::SInt(int val): _value(val) {}
}