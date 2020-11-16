#include <iostream>
#include "bencode.h"
#include <chrono>
int main() {
    auto begin = std::chrono::steady_clock::now();
    int k;
        serializer::SObj o{
                {"a", {1, 2, 3}},
                {"b", {1, 2, 3}},
                {"d", {
                        {"aa", 1},
                        {"ab", 2}
                }}
        };
        k += o["b"][2];
    std::cout << o.encode<parser::BencodeParser>() << std::endl;
    auto end = std::chrono::steady_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    std::cout << elapsed_ms.count() << std::endl;
    return 0;
}
