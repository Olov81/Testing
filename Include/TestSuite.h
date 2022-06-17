#pragma once

#include <vector>

class TestSuite
{
public:

	static TestSuite* Instance();

	typedef void(*TestFunction)();

	bool RunTests();

	void AddTest(TestFunction testFunction, const char* testName);

private:

	TestSuite();

	struct Test
	{
		Test(TestFunction function, const char* name)
			:_function(function)
			,_name(name)

		{
		}

		TestFunction _function;
		const char* _name;
	};

	std::vector<Test> _testFunctions;

	static TestSuite* _pInstance;
};