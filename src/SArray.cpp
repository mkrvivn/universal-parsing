//
// Created by pgkg on 14.11.2020.
//

#include "bencode.h"
#include <sstream>
namespace serializer
{
    SArray::SArray(VectorPtr val) : _value(val) {}

    SObj& SArray::operator[](int pos) {
        return (*_value)[pos];
    }

    VectorPtr SArray::getValue() const {
        return _value;
    }
}