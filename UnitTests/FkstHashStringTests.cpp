/**
 * Digests taken from official specifications and
 * https://tools.ietf.org/html/rfc4634#page-7
 */

#include "pch.h"
#include "CppUnitTest.h"
#include "../sha-224/fkstHashString.h"
#include <iostream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using std::string;

namespace UnitTests
{
    TEST_CLASS(FkstHashStringTests)
    {
    public:
        TEST_METHOD(Test_Input_String_abc)
        {
            const string actualDigest{ FkstHashString::sha224("abc") };
            const string expectedDigest{ "23097d223405d8228642a477bda255b32aadbce4bda0b3f7e36c9da7" };

            Assert::AreEqual(expectedDigest, actualDigest);
        }
        TEST_METHOD(Test_Input_String_empty)
        {
            const string actualDigest{ FkstHashString::sha224("") };
            const string expectedDigest{ "d14a028c2a3a2bc9476102bb288234c415a2b01f828ea62ac5b3e42f" };

            Assert::AreEqual(expectedDigest, actualDigest);
        }
        TEST_METHOD(Test_Input_String_a1000000Times)
        {
            std::stringstream ss;
            for (int i = 0; i < 1000000; ++i)
            {
                ss << 'a';
            }

            const string actualDigest{ FkstHashString::sha224(ss.str()) };
            const string expectedDigest{ "20794655980c91d8bbb4c1ea97618a4bf03f42581948b2ee4ee7ad67" };

            Assert::AreEqual(expectedDigest, actualDigest);
        }
    };
}
