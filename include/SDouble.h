//
// Created by pgkg on 17.11.2020.
//

#ifndef BENCODE_SDOUBLE_H
#define BENCODE_SDOUBLE_H
#include <string>
namespace serializer
{
    class SDouble
    {
    public:
        SDouble() = default;
        SDouble(double val);
        template<class Parser>
        std::string encode() const;
        operator double () const;
        double getValue() const;
        static SDouble createDouble(double);
    private:
        double _value;
    };
}

#endif //BENCODE_SDOUBLE_H
