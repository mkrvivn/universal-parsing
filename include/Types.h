//
// Created by pgkg on 17.11.2020.
//

#ifndef BENCODE_TYPES_H
#define BENCODE_TYPES_H

#include <vector>
#include <map>
#include <memory>
#include <variant>

namespace serializer
{
    class SBoolean;
    class SInt;
    class SDouble;
    class SString;
    class SArray;
    class SDict;
    class SObj;

    typedef std::variant<SBoolean, SInt, SDouble, SString, SArray, SDict> SData;
    typedef std::optional<SData> SDataOpt;

    typedef std::vector<SObj> ArrayVector;
    typedef std::map<SString, SObj> DictMap;
    typedef std::shared_ptr<ArrayVector> VectorPtr;
    typedef std::shared_ptr<DictMap> MapPtr;

    enum class Type
    {
        Null,
        Boolean,
        Int,
        Double,
        String,
        Array,
        Pair,
        Dict

    };
}
#endif //BENCODE_TYPES_H
