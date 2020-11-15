//
// Created by pgkg on 15.11.2020.
//

#ifndef BENCODE_EXCEPTION_H
#define BENCODE_EXCEPTION_H
#include <exception>
class BadType : public std::exception
{
    const char* what() const throw ()
    {
        return "Wrong access type";
    }
};
#endif //BENCODE_EXCEPTION_H
