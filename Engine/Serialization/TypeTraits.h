#pragma once

#include <type_traits>
#include <string>

class JSONSerializer;

// Source: https://en.cppreference.com/w/cpp/types/void_t
// Source: https://www.cppstories.com/2019/07/detect-overload-from-chars/
template<class T1, class T2 = void>
struct IsWriteable : std::false_type {};

template<class T>
struct IsWriteable<T, std::void_t<decltype(
    std::declval<JSONSerializer>().Write(std::declval<const std::string&>(), std::declval<const T&>()))>> : std::true_type {};

template<class T1, class T2 = void>
struct IsReadable : std::false_type {};

template<class T>
struct IsReadable<T, std::void_t<decltype(
    std::declval<JSONSerializer>().Read(std::declval<const std::string&>(), std::declval<T&>()))>> : std::true_type {};
