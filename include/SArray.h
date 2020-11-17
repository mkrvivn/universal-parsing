//
// Created by pgkg on 17.11.2020.
//

#ifndef BENCODE_SARRAY_H
#define BENCODE_SARRAY_H
#include "Types.h"

namespace serializer
{
    class SArray
    {
    public:
        SArray() = default;
        SArray(std::shared_ptr<std::vector<SObj>> val);
        template<class Parser>
        std::string encode() const;
        VectorPtr getValue() const;
        SObj& operator[](int pos);
        void pushBack(SObj);
        static SArray createArray();
    private:
        VectorPtr _value;
    };
}


#endif //BENCODE_SARRAY_H
