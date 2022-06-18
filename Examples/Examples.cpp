#include "FluentAssertions.h"
#include "Test.h"
#include "TestSuite.h"

int main()
{
    return TestSuite::Instance()->RunTests() ? 0 : -1;
}

TEST(Exceptions)
{
    throw std::exception("Det blev fel");
}

TEST(Number)
{
    Assert(5).equals(6);
}

TEST(Strings)
{
    std::string v1 = "apa";
    std::string v2 = "bulle";

    Assert(v1).equals(v2);
}