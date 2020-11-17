//
// Created by pgkg on 17.11.2020.
//

#ifndef BENCODE_SINT_H
#define BENCODE_SINT_H
#include <string>
namespace serializer
{
    class SInt
    {
    public:
        SInt() = default;
        SInt(int val);
        template<class Parser>
        std::string encode() const;
        operator int() const;
        int getValue() const;
        static SInt createInt(int);
    private:
        int _value;
    };
}

#endif //BENCODE_SINT_H
