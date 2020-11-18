//
// Created by pgkg on 17.11.2020.
//

#ifndef BENCODE_SOBJ_H
#define BENCODE_SOBJ_H
#include "SBoolean.h"
#include "SInt.h"
#include "SDouble.h"
#include "SString.h"
#include "SArray.h"
#include "SDict.h"

namespace serializer
{
    class SObj
    {
    public:
        SObj() = default;
        SObj(bool val);
        SObj(int val);
        SObj(double val);
        SObj(const char* val);
        SObj(SBoolean);
        SObj(SInt i);
        SObj(SDouble d);
        SObj(SString s);
        SObj(SArray a);
        SObj(SDict d);
        SObj(std::initializer_list<SObj> il);
        template<class Parser>
        std::string encode() const;
        SObj& operator[](int pos);
        SObj& operator[](const char* key);
        SDataOpt getValue() const;
        operator void*() const;
        operator bool() const;
        operator int() const;
        operator double() const;
        operator std::string() const;
        operator SBoolean() const;
        operator SInt() const;
        operator SDouble() const;
        operator SString() const;
        operator SArray() const;
        operator SDict() const;
    private:
        Type _type;
        mutable std::string _cache;
        std::optional<SData> _value;
    private:
        template<class Parser>
        std::string cache() const;
    };
}
#endif //BENCODE_SOBJ_H
