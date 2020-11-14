//
// Created by pgkg on 14.11.2020.
//

#ifndef BENCODE_MOVE_WRAPPER_H
#define BENCODE_MOVE_WRAPPER_H
#include <utility>

template<class Type>
class move_wrapper
{
public:
    template<class ...Args>
    move_wrapper(Args&&... args):
        _value(std::forward<Args>(args)...)
    {}

    move_wrapper(Type&& value) :
        _value(std::move(value)){};

    move_wrapper(move_wrapper&& rhs) = default;
    move_wrapper& operator=(move_wrapper&& rhs) = default;

    move_wrapper& operator=(const move_wrapper& rhs) = delete;
    move_wrapper& operator=(move_wrapper rhs) = delete;
    move_wrapper(const move_wrapper& rhs) = delete;
    move_wrapper() = delete;

    Type& operator*()
    {
        return _value;
    }


private:
    Type _value;
};
#endif //BENCODE_MOVE_WRAPPER_H
