//
// Created by pgkg on 14.11.2020.
//

#include "bencode.h"
#include <sstream>
namespace serializer
{

    std::string& SString::getValue() const {
        return *_value;
    }

    SString::SString(std::string val): _value(std::make_shared<std::string>(val)) {
    }

    SString::operator std::string () const {
        return *_value;
    }

    SString SString::createString(std::string s) {
        return SString(s);
    }
}