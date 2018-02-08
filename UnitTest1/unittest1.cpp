#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		TEST_METHOD(vectorTest)
		{
			// TODO: Your test code here
            CSTL::vector<int>::iterator last;
            CSTL::vector<int> v0;
            v0.push_back(0);
            v0.push_back(1);
            v0.push_back(2);
            int sum = 0;
            for (auto i = v0.begin(); i != v0.end(); ++i) {
                sum += *i;
            }
            Assert::AreEqual(sum, 3);
            last = v0.end()-1;
            Assert::AreEqual(*last, 2);
            v0.pop_back();
            last = v0.end() - 1;
            Assert::AreEqual(*last, 1);
            v0.pop_back();
            last = v0.end() - 1;
            Assert::AreEqual(*last, 0);
		}
        TEST_METHOD(listTest)
        {

        }
	};
}