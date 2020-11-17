//
// Created by pgkg on 18.11.2020.
//

#ifndef BENCODE_EXCEPTIONS_H
#define BENCODE_EXCEPTIONS_H
#include <exception>
class BadType : public std::exception
{
    const char* what() const throw ()
    {
        return "Wrong access type";
    }
};
#endif //BENCODE_EXCEPTIONS_H
