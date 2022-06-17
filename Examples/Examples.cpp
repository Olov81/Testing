#include "Assert.h"
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
    throw std::exception("Det blev ett annat fel");
}