#include "TestSuite.h"
#include <iostream>

TestSuite * TestSuite::Instance()
{
	if (_pInstance == nullptr)
	{
		_pInstance = new TestSuite();
	}

	return _pInstance;
}

bool TestSuite::RunTests()
{
	for (auto& testFunction : _testFunctions)
	{
		try
		{

			std::cout << "Running test " << testFunction._name << "... ";
			testFunction._function();
			std::cout << "passed!" << std::endl;
		}
		catch(const std::exception& e)
		{
			std::cout
			<< std::endl
			<< "Fail:" << std::endl
			<< e.what() << std::endl;
		}
		catch (...)
		{
			return false;
		}
	}
	return true;
}

void TestSuite::AddTest(TestFunction testFunction, const char* testName)
{
	Test test(testFunction, testName);

	_testFunctions.push_back(test);
}

TestSuite::TestSuite() = default;

TestSuite* TestSuite::_pInstance;