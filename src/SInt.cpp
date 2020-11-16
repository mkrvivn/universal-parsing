//
// Created by pgkg on 14.11.2020.
//

#include "bencode.h"
#include <sstream>
namespace serializer
{
    SInt::SInt(int val): _value(val) {}

    int SInt::getValue() const {
        return _value;
    }

    SInt::operator int() const {
        return _value;
    }

    SInt SInt::createInt(int i) {
        return SInt(i);
    }
}