cmake_minimum_required(VERSION 3.17)
project(bencode)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-O3")
include_directories(include/ include)
add_executable(bencode main.cpp src/SInt.cpp src/SString.cpp src/SArray.cpp src/SDict.cpp src/SObj.cpp src/BencodeParser.cpp src/JsonParser.cpp src/SBoolean.cpp src/SDouble.cpp include/MethodExistenceCheck.h src/DefaultParser.cpp include/Serializer.h include/SBoolean.h include/SInt.h include/SDouble.h include/SString.h include/SArray.h include/SDict.h include/SObj.h include/Types.h include/Encode.h include/DefaultParser.h include/JsonParser.h include/BencodeParser.h include/Exceptions.h)