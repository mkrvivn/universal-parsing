//
// Created by pgkg on 14.11.2020.
//

#include "bencode.h"
#include <sstream>
namespace serializer
{
    std::string SString::encode() const {
        std::stringstream ss;
        ss << std::to_string(_value->size()) << ":" << *_value;
        return ss.str();
    }

    std::string SString::getValue() {
        return *_value;
    }

    SString::SString(std::string val): _value(std::make_shared<std::string>(val)) {
    }

    SString::operator std::string () const {
        return *_value;
    }
}