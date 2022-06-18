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

    const TActual& actual() const
    {
        return _actual;
    }

    const char* actualName() const
    {
        return _actualName;
    }

    long line() const
    {
        return _line;
    }

    const char* file() const
    {
        return _file;
    }
    
private:

    TActual _actual;
    long _line;
    const char* _file;
    const char* _actualName;
};

template<class TActual>
class AssertionsBase
{
public:
    
    explicit AssertionsBase(const AssertionContext<TActual>& context)
        : _context(context)
    {
    }

    template<class TExpected> requires Equatable<TActual, TExpected>
    void equals(const TExpected& expected)
    {
        assert(
            actual() == expected,
            [&](auto& s){ s << "Expected " << actualName() << " to be " << expected << ", but was " << actual();});
    }
    
protected:

    const TActual& actual() const
    {
        return _context.actual();
    }

    const char* actualName() const
    {
        return _context.actualName();
    }
    
    void assert(bool condition, const std::function<void(std::stringstream&)>& appendMessage) const
    {
        if(!condition)
        {
            std::stringstream s;
            s << _context.file() << "(" << _context.line() << "):" << std::endl;
            appendMessage(s);
            throw std::exception(s.str().c_str());
        }
    }
    
private:

    AssertionContext<TActual> _context;
};

template<class TActual>
class Assertions : public AssertionsBase<TActual> 
{
public:
    
    Assertions(const AssertionContext<TActual>& context)
        : AssertionsBase<TActual>(context)
    {
        
    }
};

template<>
class Assertions<bool> : public AssertionsBase<bool>
{
public:
    
    Assertions(const AssertionContext<bool>& context)
        : AssertionsBase<bool>(context)
    {
        
    }

    void isTrue() const
    {
        assert(
            actual(),
            [&](auto& s){ s << "Expected " << actualName() << " to be true, but was false";});
    }
};

template<class TActual>
Assertions<TActual> assert(
    const TActual& actual,
    long line,
    const char* file,
    const char* actualName)
{
    return Assertions<TActual>(AssertionContext<TActual>(actual, line, file, actualName));
}

#define Assert(actual) assert(actual, __LINE__, __FILE__, #actual)