//
// Created by pgkg on 18.11.2020.
//

#ifndef BENCODE_EXCEPTIONS_H
#define BENCODE_EXCEPTIONS_H
#include <exception>
namespace serializer
{
    namespace exceptions
    {
        class BadType : public std::exception
        {
            const char* what() const throw ()
            {
                return "Wrong access type";
            }
        };

        class ParsingFailed : public std::exception
        {
            const char* what() const throw ()
            {
                return "Parsing Failed";
            }
        };
    }
}

#endif //BENCODE_EXCEPTIONS_H
