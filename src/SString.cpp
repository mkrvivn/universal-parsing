//
// Created by pgkg on 14.11.2020.
//

#include "SString.h"
#include <sstream>
namespace serializer
{
    SString::SString(std::string val): _value(std::make_shared<std::string>(std::move(val))) {
    }

    std::string& SString::getValue() const {
        return *_value;
    }

    SString::operator std::string () const {
        return *_value;
    }

    SString SString::createString(std::string s) {
        return SString(std::move(s));
    }
}