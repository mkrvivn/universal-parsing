//
// Created by pgkg on 14.11.2020.
//

#include "bencode.h"
#include <sstream>
namespace serializer
{
    std::string SInt::encode() const {
        std::stringstream ss;
        ss << "i" << std::to_string(_value) << "e";
        return ss.str();
    }

    SInt::SInt(int val): _value(val) {}

    int SInt::getValue() {
        return _value;
    }

    SInt::operator int() const {
        return _value;
    }
}