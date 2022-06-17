#pragma once
#include <iostream>
#include "TestSuite.h"

#define TEST(name)\
static void name();\
static bool init##name()\
{\
	TestSuite::Instance()->AddTest(name, #name);\
	return true;\
}\
static bool name##initialized = init##name();\
void name()

// #define ASSERT_EQUAL(expected, actual)\
// AssertEqual(expected, actual, __LINE__, __FILE__, #actual);
//
// #define ASSERT_CLOSE(expected, actual, precision)\
// AssertClose(expected, actual, precision, __LINE__, __FILE__, #actual);
//
// #define ASSERT_GREATER(limit, actual)\
// AssertGreater(limit, actual, __LINE__, __FILE__, #actual);
//
// #define ASSERT_LESS(limit, actual)\
// AssertLess(limit, actual, __LINE__, __FILE__, #actual);
//
// #define Assert(actual) return CreateAssert(actual, __LINE__, __FILE__, #actual)
//
// template<class TElement>
// static std::ostream& operator << (std::ostream& stream, const std::vector<TElement>& v)
// {
// 	if (v.size() == 0)
// 	{
// 		stream << "{ }";
//
// 		return stream;
// 	}
//
// 	stream << "{ ";
//
// 	for (size_t index = 0; index < v.size() - 1; ++index)
// 	{
// 		stream << v[index] << ", ";
// 	}
//
// 	stream << v.back() << " }";
//
// 	return stream;
// }
//
// template<class TActual>
// class Assertion
// {
// public:
//
// 	template<class TExpected>
// 	void AreAllEqualTo(const std::initializer_list<TExpected>& expectedInitializer)
// 	{
// 		std::vector<TExpected> expected(expectedInitializer);
// 		
// 		if (expected.size() != _actual.size())
// 		{
// 			FailAssert(expected);
// 		}
//
// 		for (size_t index = 0; index < expected.size(); ++index)
// 		{
// 			if (!(expected[index] == _actual[index]))
// 			{
// 				FailAssert(expected);
// 			}
// 		}
// 	}
//
// 	Assertion(const std::vector<TActual>& actual, long line, const char* file, const char* actualName)
// 		:_actual(actual)
// 		,_line(line)
// 		,_file(file)
// 		,_actualName(actualName)
// 	{
// 	}
//
// private:
//
// 	template<class TExpected>
// 	void FailAssert(const std::vector<TExpected>& expected)
// 	{
// 		std::cout << std::endl << _file << "(" << _line << "): Expected " << _actualName << " to be " << expected << " but was " << _actual << std::endl;
// 		throw std::exception("Test failed");
// 	}
//
// 	std::vector<TActual> _actual;
// 	long _line;
// 	const char* _file;
// 	const char* _actualName;
// };
//
// template<class TActual>
// static Assertion<TActual> CreateAssert(const std::vector<TActual>& actual, long line, const char* file, const char* actualName)
// {
// 	return Assertion<TActual>(actual, line, file, actualName);
// }
//
//
// template<class TExpected, class TActual>
// void AssertEqual(TExpected expected, TActual actual, long line, const char* file, const char* expectedName)
// {
// 	if (!(expected == actual))
// 	{
// 		std::cout << std::endl << file << "(" << line << "): Expected " << expectedName << " to be " << expected << " but was " << actual << std::endl;
// 		throw std::exception("Test failed");
// 	}
// }
//
// template<class TExpected, class TActual>
// void AssertClose(TExpected expected, TActual actual, double precision, long line, const char* file, const char* expectedName)
// {
// 	if (!(std::abs(expected - actual) < precision))
// 	{
// 		std::cout << std::endl << file << "(" << line << "): Expected " << expectedName << " to be approximately " << expected << " but was " << actual << std::endl;
// 		throw std::exception("Test failed");
// 	}
// }
//
// template<class TLimit, class TActual>
// void AssertGreater(TLimit limit, TActual actual, long line, const char* file, const char* expectedName)
// {
// 	if (!(actual > limit))
// 	{
// 		std::cout << std::endl << file << "(" << line << "): Expected " << expectedName << " to be greater than " << limit << " but was " << actual << std::endl;
// 		throw std::exception("Test failed");
// 	}
// }
//
// template<class TLimit, class TActual>
// void AssertLess(TLimit limit, TActual actual, long line, const char* file, const char* expectedName)
// {
// 	if (!(actual < limit))
// 	{
// 		std::cout << std::endl << file << "(" << line << "): Expected " << expectedName << " to be less than " << limit << " but was " << actual << std::endl;
// 		throw std::exception("Test failed");
// 	}
// }