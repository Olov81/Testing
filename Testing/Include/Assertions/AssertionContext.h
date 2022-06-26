#pragma once

#include <functional>

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