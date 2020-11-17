//
// Created by pgkg on 16.11.2020.
//

#include "SBoolean.h"
namespace serializer{


    bool SBoolean::getValue() const {
        return _value;
    }

    SBoolean SBoolean::createBoolean(bool val) {
        return SBoolean(val);
    }

    SBoolean::operator bool() const {
        return _value;
    }

    SBoolean::SBoolean(bool val) : _value(val) {}
}