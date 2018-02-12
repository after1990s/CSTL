#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{		
	TEST_CLASS(listTest)
	{
	public:
        TEST_METHOD(listTestInit)
        {
            CSTL::list<int> l0;
            l0.push_back(0);
            l0.push_back(1);
            l0.push_back(2);
            l0.push_back(3);
            auto itr = l0.begin();
            Assert::AreEqual(*itr, 0);
            itr++;
            Assert::AreEqual(*itr, 1);
            itr++;
            Assert::AreEqual(*itr, 2);
            itr++;
            Assert::AreEqual(*itr, 3);
            itr++;
            Assert::IsTrue(itr == l0.end());

        }

        TEST_METHOD(lisItrTest)
        {
            CSTL::list<int> l0;
            l0.push_back(0);
            l0.push_back(1);
            l0.push_back(2);
            l0.push_back(3);
            //test remove not influnce exiting itr
            auto l0_itr1 = l0.begin();
            l0_itr1++;
            l0_itr1++;
            l0.pop_back();
            Assert::AreEqual(*l0_itr1, 2);
            l0_itr1++;
            Assert::IsTrue(l0_itr1 == l0.end());
            auto l0_itr2 = l0.end();
            l0_itr2--;
            l0_itr2--;
            l0_itr2--;
            Assert::IsTrue(l0_itr2 == l0.begin());
        }

        //remove unique
        TEST_METHOD(listApiTest)
        {
            CSTL::list<int> l0;
            l0.push_back(0);
            l0.push_back(1);
            l0.push_back(2);
            l0.push_back(0);
            l0.push_back(0);
            l0.push_back(1);
            l0.push_back(2);

            l0.unique();
            Assert::AreEqual(l0.size() , (size_t)6);
            l0.remove(0);
            Assert::AreEqual(l0.size(), (size_t)4);

            CSTL::list<int> l1;
            l1.unique();
            Assert::AreEqual(l1.size(), (size_t)0);
            l1.remove(0);
            Assert::AreEqual(l1.size(), (size_t)0);
        }
        TEST_METHOD(swapTest)
        {
            CSTL::list<int> l0;
            l0.push_back(1);
            l0.push_back(2);
            l0.push_back(3);
            CSTL::list<int> l1;
            l1.push_back(4);
            l1.push_back(5);
            l1.push_back(6);
            l1.push_back(7);

            l0.swap(l1);
            Assert::AreEqual((size_t)4, l0.size());
            Assert::AreEqual((size_t)3, l1.size());
            int sum0 = CSTL::accumulate(l0.begin(), l0.end(), 0);
            int sum1 = CSTL::accumulate(l1.begin(), l1.end(), 0);
            Assert::AreEqual(6, sum1);
            Assert::AreEqual(22, sum0);

        }
	};
}