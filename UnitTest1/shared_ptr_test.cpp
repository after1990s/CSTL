#include "stdafx.h"
#include "CppUnitTest.h"
#include <memory>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
    TEST_CLASS(SharedPtrTest)
    {
    public:
        TEST_METHOD(shared_ptr_count_test)
        {
            int *i = new int;
            CSTL::shared_ptr_count ct0;
            ct0.acquire(i);
            ct0.acquire(i);
            Assert::AreEqual((long)2, ct0.use_count());
            CSTL::shared_ptr_count ct1 = ct0;
            ct1.acquire(i);
            Assert::AreEqual((long)3, ct1.use_count());
            Assert::AreEqual((long)3, ct0.use_count());
            ct1.release(i);
            Assert::AreEqual((long)2, ct0.use_count());
            Assert::AreEqual((long)2, ct1.use_count());
            ct1.release(i);
            Assert::AreEqual((long)1, ct0.use_count());
            Assert::AreEqual((long)1, ct1.use_count());
            ct1.release(i);
            Assert::AreEqual((long)0, ct0.use_count());
            Assert::AreEqual((long)0, ct1.use_count());
            ct1.release(i);
            Assert::AreEqual((long)0, ct0.use_count());
            Assert::AreEqual((long)0, ct1.use_count());

            int *i0 = new int(7);
            auto d_i0 = [](int *i) {
                delete i;
                OutputDebugStringA("d_i0 called");
            };
            CSTL::shared_ptr_count ct2;
            ct2.acquire(i0);
            ct2.release(i0, &d_i0);

            std::shared_ptr<int> k(new int(7), d_i0);
            k.reset();
        }
    
        TEST_METHOD(shared_ptr_test) {
            CSTL::shared_ptr<int> ct0;
            Assert::AreEqual((int*)nullptr, ct0.get());

            CSTL::shared_ptr<int> ct1(new int(7));
            Assert::AreEqual((long)1, ct1.use_count());

            ct0 = ct1;
            Assert::AreEqual((long)2, ct0.use_count());
            Assert::AreEqual((long)2, ct1.use_count());
            {
                auto ct2 = ct1;
                Assert::AreEqual((long)3, ct0.use_count());
                Assert::AreEqual((long)3, ct1.use_count());
                Assert::AreEqual((long)3, ct2.use_count());
            }
            Assert::AreEqual((long)2, ct0.use_count());
            Assert::AreEqual((long)2, ct1.use_count());
            ct0.reset();
            Assert::AreEqual((long)1, ct0.use_count());
            Assert::AreEqual((long)1, ct1.use_count());
            


        }
    };
}