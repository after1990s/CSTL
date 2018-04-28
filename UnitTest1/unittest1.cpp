#include "stdafx.h"
#include "CppUnitTest.h"
#include <memory>
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
bool _stdcall unary_func_0() {
    return true;
}
bool _cdecl unary_func_1() {
    return true;
}
bool _fastcall unary_func_2() {
    return true;
}
bool _stdcall unary_func_3(int a) {
    return true;
}
bool _cdecl unary_func_4(int a, int b) {
    return true;
}
namespace UnitTest1
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		TEST_METHOD(vectorTest)
		{
			// TODO: Your test code here
            CSTL::vector<int> v0;

            CSTL::vector<int>::iterator last = v0.end();
            v0.push_back(0);
            v0.push_back(1);
            v0.push_back(2);
            Assert::AreEqual(v0[0], 0);
            Assert::AreEqual(v0[1], 1);
            Assert::AreEqual(v0[2], 2);
            
            last = v0.end()-1;
            Assert::AreEqual(*last, 2);
            v0.pop_back();
            last = v0.end() - 1;
            Assert::AreEqual(*last, 1);
            v0.pop_back();
            last = v0.end() - 1;
            Assert::AreEqual(*last, 0);
            v0.pop_back();
            Assert::AreEqual((int)v0.size(), 0);
        }
        TEST_METHOD(listTest)
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

            //test remove not influnce exiting itr
            auto l0_itr1 = l0.begin();
            l0_itr1++;
            l0_itr1++;
            l0.pop_back();
            Assert::AreEqual(*l0_itr1, 2);
            l0_itr1++;
            Assert::IsTrue(l0_itr1 == l0.end());

            //std::vector<int> v3;
            //CSTL::vector<int> v4={ 1,2,3,4,5 };


        }
        TEST_METHOD(sharedPtrTest) {
            int n[10] = { 1 };
            std::shared_ptr<decltype(n)> pt(new int(3));
            Assert::AreEqual(3, (pt)[11]);
        }
        TEST_METHOD(metaUtilTest) {
            Assert::AreEqual(true, std::is_same<int, CSTL::remove_reference<int&>::type>::value);
            Assert::AreEqual(true, std::is_same<int, CSTL::remove_reference<int&&>::type>::value);
            Assert::AreEqual(true, std::is_same<int, CSTL::remove_reference<int>::type>::value);
            Assert::AreEqual(false, std::is_same<double, CSTL::remove_reference<int&>::type>::value);            


            Assert::AreEqual(true, std::is_same<int, CSTL::remove_const<const int>::type>::value);
            //Assert::AreEqual(true, std::is_same<int&, CSTL::remove_const<const int&>::type>::value); same as std::remove_const
           // Assert::AreEqual(true, std::is_same<int&&, CSTL::remove_const<const int&&>::type>::value);
            Assert::AreEqual(false, std::is_same<double, CSTL::remove_const<const int>::type>::value);

            Assert::AreEqual(true, std::is_same<int, CSTL::remove_volatile<volatile int>::type>::value);
            //Assert::AreEqual(true, std::is_same<int&, CSTL::remove_volatile<volatile int&>::type>::value); same as std::remove_const
            //Assert::AreEqual(true, std::is_same<int&&, CSTL::remove_volatile<volatile int&&>::type>::value);
            Assert::AreEqual(false, std::is_same<double, CSTL::remove_volatile<volatile int>::type>::value);
            
            Assert::AreEqual(true, std::is_same<int, CSTL::remove_cv<volatile const int>::type>::value);
            Assert::AreEqual(true, std::is_same<int, CSTL::remove_cv<const volatile int>::type>::value);


            Assert::AreEqual(true, std::is_same<int, CSTL::remove_extent<int [7]>::type>::value);
            Assert::AreEqual(false, std::is_same<int[7], CSTL::remove_extent<int [7]>::type>::value);


            Assert::AreEqual(7, CSTL::extent<int[7]>::value);
            Assert::AreEqual(0, CSTL::extent<int[]>::value);

            Assert::AreEqual(true, std::is_same<const int&, CSTL::add_const_lvalue_reference<int&&>::type>::value);
            Assert::AreEqual(true, std::is_same<const int&, CSTL::add_const_lvalue_reference<int&>::type>::value);
            Assert::AreEqual(true, std::is_same<const int&, CSTL::add_const_lvalue_reference<int>::type>::value);

            Assert::AreEqual(true, __is_convertible_to(double, int));

            Assert::AreEqual(false, CSTL::is_unary_function<decltype(&unary_func_0)>::value);
            Assert::AreEqual(true, CSTL::is_unary_function<decltype(&unary_func_1)>::value);
            Assert::AreEqual(true, CSTL::is_unary_function<decltype(&unary_func_2)>::value);
            Assert::AreEqual(true, CSTL::is_unary_function<decltype(&unary_func_3)>::value);
            Assert::AreEqual(false, CSTL::is_unary_function<decltype(&unary_func_4)>::value);         
        }
	};
}