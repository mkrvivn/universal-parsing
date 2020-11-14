#include <iostream>
#include "bencode.h"
int main() {
    serializer::SObj o = {{"a", 1}, {"b", 2}, {"b", 2}, {"b", 2}, {"a", {1,2 ,3 ,4, 5, 6, 7}}};
    std::cout << o.encode() << std::endl;
    return 0;
}
