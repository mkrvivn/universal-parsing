//
// Created by pgkg on 17.11.2020.
//

#ifndef BENCODE_METHODEXISTENCECHECK_H
#define BENCODE_METHODEXISTENCECHECK_H

#include <type_traits>

template<typename, typename T>
struct is_exist_null {
    static_assert(
            std::integral_constant<T, false>::value,
            "Second template parameter needs to be of function type.");
};

template<typename C, typename Ret, typename... Args>
struct is_exist_null<C, Ret(Args...)> {
private:
    template<typename T>
    static constexpr auto check(T*)
    -> typename
    std::is_same<
            decltype( std::declval<T>().NullToText( std::declval<Args>()... ) ),
            Ret    // ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
    >::type;  // attempt to call it and see if the return type is correct

    template<typename>
    static constexpr std::false_type check(...);

    typedef decltype(check<C>(0)) type;

public:
    static constexpr bool value = type::value;
};


template<typename, typename T>
struct is_exist_boolean {
    static_assert(
            std::integral_constant<T, false>::value,
            "Second template parameter needs to be of function type.");
};

template<typename C, typename Ret, typename... Args>
struct is_exist_boolean<C, Ret(Args...)> {
private:
    template<typename T>
    static constexpr auto check(T*)
    -> typename
    std::is_same<
            decltype( std::declval<T>().BooleanToText( std::declval<Args>()... ) ),
            Ret    // ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
    >::type;  // attempt to call it and see if the return type is correct

    template<typename>
    static constexpr std::false_type check(...);

    typedef decltype(check<C>(0)) type;

public:
    static constexpr bool value = type::value;
};

template<typename, typename T>
struct is_exist_int {
    static_assert(
            std::integral_constant<T, false>::value,
            "Second template parameter needs to be of function type.");
};

template<typename C, typename Ret, typename... Args>
struct is_exist_int<C, Ret(Args...)> {
private:
    template<typename T>
    static constexpr auto check(T*)
    -> typename
    std::is_same<
            decltype( std::declval<T>().IntToText( std::declval<Args>()... ) ),
            Ret    // ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
    >::type;  // attempt to call it and see if the return type is correct

    template<typename>
    static constexpr std::false_type check(...);

    typedef decltype(check<C>(0)) type;

public:
    static constexpr bool value = type::value;
};

template<typename, typename T>
struct is_exist_double {
    static_assert(
            std::integral_constant<T, false>::value,
            "Second template parameter needs to be of function type.");
};

template<typename C, typename Ret, typename... Args>
struct is_exist_double<C, Ret(Args...)> {
private:
    template<typename T>
    static constexpr auto check(T*)
    -> typename
    std::is_same<
            decltype( std::declval<T>().DoubleToText( std::declval<Args>()... ) ),
            Ret    // ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
    >::type;  // attempt to call it and see if the return type is correct

    template<typename>
    static constexpr std::false_type check(...);

    typedef decltype(check<C>(0)) type;

public:
    static constexpr bool value = type::value;
};

template<typename, typename T>
struct is_exist_string {
    static_assert(
            std::integral_constant<T, false>::value,
            "Second template parameter needs to be of function type.");
};

template<typename C, typename Ret, typename... Args>
struct is_exist_string<C, Ret(Args...)> {
private:
    template<typename T>
    static constexpr auto check(T*)
    -> typename
    std::is_same<
            decltype( std::declval<T>().StringToText( std::declval<Args>()... ) ),
            Ret    // ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
    >::type;  // attempt to call it and see if the return type is correct

    template<typename>
    static constexpr std::false_type check(...);

    typedef decltype(check<C>(0)) type;

public:
    static constexpr bool value = type::value;
};

template<typename, typename T>
struct is_exist_array {
    static_assert(
            std::integral_constant<T, false>::value,
            "Second template parameter needs to be of function type.");
};

template<typename C, typename Ret, typename... Args>
struct is_exist_array<C, Ret(Args...)> {
private:
    template<typename T>
    static constexpr auto check(T*)
    -> typename
    std::is_same<
            decltype( std::declval<T>().ArrayToText( std::declval<Args>()... ) ),
            Ret    // ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
    >::type;  // attempt to call it and see if the return type is correct

    template<typename>
    static constexpr std::false_type check(...);

    typedef decltype(check<C>(0)) type;

public:
    static constexpr bool value = type::value;
};

template<typename, typename T>
struct is_exist_dict {
    static_assert(
            std::integral_constant<T, false>::value,
            "Second template parameter needs to be of function type.");
};

template<typename C, typename Ret, typename... Args>
struct is_exist_dict<C, Ret(Args...)> {
private:
    template<typename T>
    static constexpr auto check(T*)
    -> typename
    std::is_same<
            decltype( std::declval<T>().DictToText( std::declval<Args>()... ) ),
            Ret    // ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
    >::type;  // attempt to call it and see if the return type is correct

    template<typename>
    static constexpr std::false_type check(...);

    typedef decltype(check<C>(0)) type;

public:
    static constexpr bool value = type::value;
};

template<typename, typename T>
struct is_exist_obj {
    static_assert(
            std::integral_constant<T, false>::value,
            "Second template parameter needs to be of function type.");
};

template<typename C, typename Ret, typename... Args>
struct is_exist_obj<C, Ret(Args...)> {
private:
    template<typename T>
    static constexpr auto check(T*)
    -> typename
    std::is_same<
            decltype( std::declval<T>().ObjToText( std::declval<Args>()... ) ),
            Ret    // ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
    >::type;  // attempt to call it and see if the return type is correct

    template<typename>
    static constexpr std::false_type check(...);

    typedef decltype(check<C>(0)) type;

public:
    static constexpr bool value = type::value;
};
#endif //BENCODE_METHODEXISTENCECHECK_H
