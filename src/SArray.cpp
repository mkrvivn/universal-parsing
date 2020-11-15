//
// Created by pgkg on 14.11.2020.
//

#include "bencode.h"
#include <sstream>
namespace serializer
{
    SArray::SArray(VectorPtr val) : _value(val) {}

    std::string SArray::encode() const {
        std::stringstream ss;
        ss << "l";
        for(SObj& i : *_value)
        {
            ss << i.encode();
        }
        ss << "e";
        return ss.str();
    }

    SObj& SArray::operator[](int pos) {
        return (*_value)[pos];
    }
}