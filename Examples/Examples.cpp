#include "FluentAssertions.h"
#include "Test.h"
#include "TestSuite.h"

int main()
{
    return TestSuite::Instance()->RunTests() ? 0 : -1;
}

TEST(Apa)
{
    throw std::exception("Det blev fel");
}

TEST(Bepa)
{
    Assert(5).equals(6);
}