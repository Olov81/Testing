#pragma once

#include "AssertionContext.h"
#include "Fail.h"

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

    template<class TExpected>
    void assert(bool condition, const TExpected& expected, const char* requirement) const
    {
        return assert(condition, expected, actual(), requirement);
    }
    
    template<class TExpected, class T>
    void assert(bool condition, const TExpected& expected, const T& actual, const char* requirement) const
    {
        return assert(
            condition,
            [&](auto& s){s << "Expected " << actualName() << " to " << requirement << " " << expected << ", but was " << actual;});    
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