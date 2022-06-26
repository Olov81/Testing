#pragma once

#include <concepts>

template <typename T1, typename T2>
concept Equatable = requires(T1 a, T2 b)
{
    { a == b } -> std::convertible_to<bool>;
};

template<typename T1, typename T2>
concept Greater = requires(T1 a, T2 b)
{
    { a > b } -> std::convertible_to<bool>;    
};

template<typename T1, typename T2>
concept Subtractable = requires(T1 a, T2 b)
{
    { a - b } -> std::convertible_to<double>;    
};

template<class TVector>
using Iterator = std::decay_t<decltype(std::declval<TVector>().begin())>; 

template<class TVector>
using Element = std::decay_t<decltype(*std::declval<TVector>().begin())>; 

template<class TVector>
concept Vector = requires(TVector v)
{
    { v.begin() } -> std::convertible_to<Iterator<TVector>>;
    { v.end() } -> std::convertible_to<Iterator<TVector>>;
    { v.size() } -> std::integral; 
};