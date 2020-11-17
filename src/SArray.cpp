//
// Created by pgkg on 14.11.2020.
//
#include "SArray.h"
#include <sstream>
#include "SObj.h"
namespace serializer
{

    SArray::SArray(VectorPtr val) : _value(std::move(val)) {}

    SObj& SArray::operator[](int pos) {
        return (*_value)[pos];
    }

    VectorPtr SArray::getValue() const {
        return _value;
    }

    SArray SArray::createArray() {
        return SArray(std::make_shared<ArrayVector>());
    }

    void SArray::pushBack(SObj o) {
        _value->push_back(std::move(o));
    }
}