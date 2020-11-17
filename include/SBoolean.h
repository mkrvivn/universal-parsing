//
// Created by pgkg on 17.11.2020.
//

#ifndef BENCODE_SBOOLEAN_H
#define BENCODE_SBOOLEAN_H
#include <string>
namespace serializer
{
    class SBoolean
    {
    public:
        SBoolean() = default;
        SBoolean(bool val);
        template<class Parser>
        std::string encode() const;
        operator bool() const;
        bool getValue() const;
        static SBoolean createBoolean(bool);
    private:
        bool _value;
    };
}
#endif //BENCODE_SBOOLEAN_H
