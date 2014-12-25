/*
 * File:   unittest.h
 * Author: Kimmy Leo
 *
 * Created on 2014年4月22日, 上午11:16
 */

#ifndef UNITTEST_H
#define UNITTEST_H

#include <iostream>
#include <string>

#define TestCase(NAME)								\
	extern void TEST_CASE_FUNCTION_##NAME(void);	\
	class TEST_CASE_CLASS_##NAME					\
	{												\
	public:											\
		TEST_CASE_CLASS_##NAME()					\
		{											\
			std::cout << #NAME << std::endl;		\
			TEST_CASE_FUNCTION_##NAME();			\
		}											\
	} TEST_CASE_INSTANCE_##NAME;					\
	void TEST_CASE_FUNCTION_##NAME(void)

#define TestAssert(CONDITION) do{ if (!(CONDITION)) throw 0; } while (0)
#define TestPrint(MESSAGE) std::cout << (MESSAGE) << std::endl;

#define TestRunner() int main(){return 0;}

#endif	/* UNITTEST_H */

