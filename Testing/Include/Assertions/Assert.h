#pragma once

#include <exception>

#include "AssertionContext.h"
#include "AssertionsBase.h"
#include "Concepts.h"
#include "Fail.h"

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
        assert(actual() == expected, expected, "be");
    }

    template<class TExpected> requires Greater<TActual, TExpected>
    void isGreaterThan(const TExpected& expected)
    {
        assert(actual() > expected, expected,"be greater than");
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

template<std::floating_point TActual>
class Assertions<TActual> : public GeneralAssertions<TActual>
{
    using AssertionsBase<TActual>::actual;
    using AssertionsBase<TActual>::actualName;
    using AssertionsBase<TActual>::assert;

public:
    
    Assertions(const AssertionContext<TActual>& context)
    : GeneralAssertions<TActual>(context)
    {
    }

    template<class TExpected> requires Subtractable<TActual, TExpected>
    void isCloseTo(const TExpected& expected, const double& precision)
    {
        assert(
            std::abs(actual() - expected) < precision,
            [&](auto& s){s << "Expected " << actualName() << " to differ no more than " << precision << " from " << expected << ", but was " << actual();});
    }
};

template<Vector TActual>
class Assertions<TActual> : public GeneralAssertions<TActual>
{
    using GeneralAssertions<TActual>::actual;
    using GeneralAssertions<TActual>::assert;
    using GeneralAssertions<TActual>::actualName;
    
public:
    
    Assertions(const AssertionContext<TActual>& context)
    : GeneralAssertions<TActual>(context)
    {
    }

    template<class TElement> requires Equatable<Element<TActual>, TElement>
    void areAllEqualTo(const std::initializer_list<TElement>& expected)
    {
        areAllEqualTo<std::vector<TElement>>(expected);
    }
    
    template<Vector TExpected> requires Equatable<Element<TActual>, Element<TExpected>>
    void areAllEqualTo(const TExpected& expected)
    {
        assert(
            actual().size() == expected.size(),
            [&](auto& s){ s << "Expected " << actualName() << " to have " << expected.size() << " elements, but it had " << actual().size();});
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