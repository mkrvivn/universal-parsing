//
// Created by pgkg on 17.11.2020.
//
#include "bencode.h"
#include <sstream>
namespace serializer
{
    SDouble::SDouble(double val) : _value(val) {

    }

    double SDouble::getValue() const {
        return _value;
    }

    SDouble SDouble::createDouble(double val) {
        return SDouble(val);
    }
}
