#pragma once

#include <concepts>
#include <exception>
#include <string>
#include <functional>
#include <sstream>

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

template<class TActual>
class AssertionContext
{
public:

    explicit AssertionContext(TActual actual, long line, const char* file, const char* actualName)
    : _actual(std::move(actual))
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

inline void fail(long line, const char* file,  const std::function<void(std::stringstream&)>& appendMessage)
{
    std::stringstream s;
    s << file << "(" << line << "):" << std::endl;
    appendMessage(s);
    throw std::exception(s.str().c_str());
}

template<class TActual>
class AssertionsBase
{
public:
    
    explicit AssertionsBase(const AssertionContext<TActual>& context)
        : _context(context)
    {
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
            fail(_context.line(), _context.file(), appendMessage);
        }
    }
    
private:

    AssertionContext<TActual> _context;
};

template<class TActual>
class GeneralAssertions : public AssertionsBase<TActual>
{
protected:
    
    using AssertionsBase<TActual>::actual;
    using AssertionsBase<TActual>::actualName;
    using AssertionsBase<TActual>::assert;
    
public:

    explicit GeneralAssertions(const AssertionContext<TActual>& context)
    : AssertionsBase<TActual>(context)
    {
    }

    
    template<class TExpected> requires Equatable<TActual, TExpected>
    void equals(const TExpected& expected)
    {
        assert(
            actual() == expected,
            [&](auto& s){ s << "Expected " << actualName() << " to be " << expected << ", but was " << actual();});
    }

    template<class TExpected> requires Greater<TActual, TExpected>
    void isGreaterThan(const TExpected& expected)
    {
        assert(
            actual() > expected,
            [&](auto& s){ s << "Expected " << actualName() << " to be greater than " << expected << ", but was " << actual();});
    }
};

template<class TActual>
class Assertions : public GeneralAssertions<TActual> 
{
public:
    
    Assertions(const AssertionContext<TActual>& context)
        : GeneralAssertions<TActual>(context)
    {
        
    }
};

template<class TActual>
Assertions<TActual> assertThat(
    const TActual& actual,
    long line,
    const char* file,
    const char* actualName)
{
    return Assertions<TActual>(AssertionContext<TActual>(actual, line, file, actualName));
}

inline void assertThat(
    bool assertion,
    long line,
    const char* file,
    const char* expressionString)
{
    if(!assertion)
    {
        fail(line, file, [&](auto& s){s << "Expected " << expressionString;});
    }
}

#define ASSERT_THAT(actual) assertThat(actual, __LINE__, __FILE__, #actual)