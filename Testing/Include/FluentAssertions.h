#pragma once

#include <concepts>
#include <exception>
#include <string>
#include <functional>
#include <sstream>

template<typename T1, typename T2>
concept Equatable = requires(T1 a, T2 b)
{
    { a == b } -> std::convertible_to<bool>;
};

template<class TActual>
class AssertionContext
{
public:
    
    explicit AssertionContext(const TActual& actual, long line, const char* file, const char* actualName)
        : _actual(actual)
        , _line(line)
        , _file(file)
        , _actualName(actualName)
    {
    }

    template<class TExpected> requires Equatable<TActual, TExpected>
    void equals(const TExpected& expected)
    {
        assertThat(
            _actual == expected,
            [&](auto& s){ s << "Expected " << _actualName << " to be " << expected << ", but was " << _actual;});
    }
    
private:

    TActual _actual;
    long _line;
    const char* _file;
    const char* _actualName;
    
    void assertThat(bool condition, const std::function<void(std::stringstream&)>& appendMessage)
    {
        if(!condition)
        {
            std::stringstream s;
            s << _file << "(" << _line << "):" << std::endl;
            appendMessage(s);
            throw std::exception(s.str().c_str());
        }
    }
};

// template<class TActual>
// class AssertionContext : public AssertionContextBase<TActual> 
// {
// public:
//     
//     explicit AssertionContext(const TActual& actual)
//         : AssertionContextBase(actual)
//     {
//     }
//     
// };
//
// template<>
// class AssertionContext<bool> : public AssertionContextBase<bool>
// {
// public:
//     
//     explicit AssertionContext(const bool& actual)
//         : AssertionContextBase(actual)
//     {
//     }
//
//     void IsTrue()
//     {
//
//     }
// };

template<class TActual>
AssertionContext<TActual> assert(
    const TActual& actual,
    long line,
    const char* file,
    const char* actualName)
{
    return AssertionContext<TActual>(actual, line, file, actualName);
}

#define Assert(actual) assert(actual, __LINE__, __FILE__, #actual)