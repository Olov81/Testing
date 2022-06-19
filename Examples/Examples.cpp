#include "FluentAssertions.h"
#include "Test.h"
#include "TestSuite.h"

int main()
{
    return TestSuite::Instance()->RunTests() ? 0 : -1;
}

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