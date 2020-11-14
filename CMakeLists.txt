cmake_minimum_required(VERSION 3.17)
project(bencode)

set(CMAKE_CXX_STANDARD 20)

include_directories(include/ include)
add_executable(bencode main.cpp include/bencode.h include/move_wrapper.h src/SInt.cpp src/SString.cpp src/SArray.cpp src/SDict.cpp src/SObj.cpp)