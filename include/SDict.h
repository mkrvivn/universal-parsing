//
// Created by pgkg on 17.11.2020.
//

#ifndef BENCODE_SDICT_H
#define BENCODE_SDICT_H
#include "Types.h"
namespace serializer
{
    class SDict
    {
    public:
        SDict() = default;
        SDict(MapPtr val);
        template<class Parser>
        std::string encode() const;
        MapPtr getValue() const;
        void insert(const SString& s, const SObj& o);
        SObj& operator[](const char* key);
        static SDict createDict();
    private:
        MapPtr _value;
    };
}
#endif //BENCODE_SDICT_H
