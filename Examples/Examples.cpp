#include "FluentAssertions.h"
#include "Test.h"
#include "TestSuite.h"

int main()
{
    return TestSuite::Instance()->RunTests() ? 0 : -1;
}

class MyClass
{
public:
    
    MyClass(const char* name)
        : _name(name)
    {
        
    }

    std::string Name() const
    {
        return _name;
    }

private:
    
    std::string _name;
};

template<>
class Assertions<MyClass> : public AssertionsBase<MyClass>
{
public:

    Assertions(const AssertionContext<MyClass>& context)
        : AssertionsBase<MyClass>(context)
    {
    }
    
    void hasName(const char* expected) const
    {
        auto actualValue = actual().Name();
        assert(
            actualValue == expected,
            [&](auto& s){s << "Expected " << actualName() << " to have name " << expected << ", but it was " << actualValue;});
    }
};

TEST(success)
{
}

TEST(unknown_error)
{
    throw 1;
}

TEST(exceptions)
{
    throw std::exception("Det blev fel");
}

TEST(general_assertion)
{
    constexpr auto value = 5.0;
    ASSERT_THAT(value == 6.0);
}

TEST(number)
{
    ASSERT_THAT(5).equals(6);
}

TEST(strings)
{
    const std::string v1 = "apa";
    const std::string v2 = "bulle";

    ASSERT_THAT(v1).equals(v2);
}

TEST(greater_than)
{
    constexpr double number = 0.5;

    ASSERT_THAT(number).isGreaterThan(10);
}

TEST(custom_class)
{
    const MyClass x("Orvar");

    ASSERT_THAT(x).hasName("Bosse");
}