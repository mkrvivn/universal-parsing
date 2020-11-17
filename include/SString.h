//
// Created by pgkg on 17.11.2020.
//

#ifndef BENCODE_SSTRING_H
#define BENCODE_SSTRING_H
#include <string>
#include <memory>
namespace serializer {
    class SString
    {
    public:
        SString() = default;
        SString(std::string val);
        template<class Parser>
        std::string encode() const;
        operator std::string() const;
        std::string& getValue() const;
        bool operator<(const SString& rhs) const
        {
            return *_value < rhs.getValue();
        }
        bool operator==(const SString& rhs) const
        {
            return *_value == *rhs._value;
        }
        static SString createString(std::string);
        struct hash{
            size_t operator()(const SString& val) const {
                return std::hash<std::string>()(*val._value);
            }
        };
    private:
        std::shared_ptr<std::string> _value;
    };
}
#endif //BENCODE_SSTRING_H
