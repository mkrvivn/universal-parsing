#include <iostream>
#include "bencode.h"
int main() {
    serializer::SObj o{
            {"a", {1, 2, 3}},
            {"b", {1, 2, 3}}
    };
    std::cout << "object creation end" << std::endl;
    serializer::SArray a = o["b"];
    std::cout << "element access end" << std::endl;
    std::cout << a.encode() << std::endl;
    return 0;
}
