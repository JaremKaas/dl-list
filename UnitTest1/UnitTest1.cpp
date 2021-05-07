#include "pch.h"
#include "CppUnitTest.h"
#include "C:\Users\Asus\Documents\GitHub\dl-list\slist.h""
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(test_initialLength)
		{
			int length = 0;
			List<int,int> l;
			Assert::AreEqual(length, l.refLength());
		}
		TEST_METHOD(test_isListEmpty_1)
		{
			List<int, int> l;
			Assert::IsTrue(l.isListEmpty());
		}
		TEST_METHOD(test_doesNodeExists_1)
		{
			List<int, int> l;
			Assert::IsFalse(l.doesNodeExist(5));
		}
		TEST_METHOD(test_insert_1)
		{
			List<int, int> l;
			l.insert(5, 13);
			Assert::IsTrue(l.doesNodeExist(5));
		}

	};
}
