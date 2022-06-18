#include "TestSuite.h"
#include <iostream>
#include <chrono>

TestSuite * TestSuite::Instance()
{
	if (_pInstance == nullptr)
	{
		_pInstance = new TestSuite();
	}

	return _pInstance;
}

std::ostream& operator<<(std::ostream& stream, std::chrono::duration<long long, std::ratio<1, 10000000>> duration)
{
	auto h = std::chrono::duration_cast<std::chrono::hours>(duration);
	auto m = std::chrono::duration_cast<std::chrono::minutes>(duration - h);
	auto s = std::chrono::duration_cast<std::chrono::seconds>(duration - m);
	auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(duration - s);

	if(h.count() > 0)
	{
		stream << h.count() << "h";
	}
	if(m.count() > 0)
	{
		stream << m.count() << "m";
	}
	if(s.count() > 0)
	{
		stream << s.count() << "s";
	}
	
	return stream << ms.count() << "ms";
}

bool TestSuite::RunTests() const
{
	int passed = 0;
	int failed = 0;

	const auto start = std::chrono::system_clock::now();
	for (const auto& testFunction : _testFunctions)
	{
		try
		{

			std::cout << "Running test " << testFunction._name << "... ";
			testFunction._function();
			std::cout << "passed!";
			++passed;
		}
		catch(const std::exception& e)
		{
			std::cout
			<< std::endl
			<< "Fail: " << e.what();
			++failed;
		}
		catch (...)
		{
			std::cout << std::endl << "Fail: Unknown error";
			++failed;
		}

		std::cout << std::endl;
	}
	const auto end = std::chrono::system_clock::now();

	const auto duration = end - start;
	
	std::cout
		<< std::endl
		<< std::endl
		<< "====== Test Summary ======" << std::endl
		<< "Passed: " << passed << std::endl
		<< "Failed: " << failed << std::endl
		<< "Total run time: " << duration << std::endl
		<< "==========================" << std::endl;
	
	return failed == 0;
}

void TestSuite::AddTest(TestFunction testFunction, const char* testName)
{
	Test test(testFunction, testName);

	_testFunctions.push_back(test);
}

TestSuite::TestSuite() = default;

TestSuite* TestSuite::_pInstance;