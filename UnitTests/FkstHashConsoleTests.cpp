/**
 * Digests taken from official specifications and
 * https://tools.ietf.org/html/rfc4634#page-7
 */

#include "pch.h"
#include "CppUnitTest.h"
#include "../sha-224/fkstHashConsole.h"
#include <iostream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using std::string;

namespace UnitTests
{
    TEST_CLASS(FkstHashConsoleTests)
    {
    public:

        TEST_METHOD(Test_Input_String_MultipleOf512)
        {
            std::stringstream ss;
            // 5120 bit message, 640 symbols(bytes)
            for (int i = 0; i < 20; ++i)
            {
                ss << "01234567012345670123456701234567"; //32bytes
            }

            string asd = ss.str();
            const string actualDigest{ FkstHashConsole::sha224(ss.str()) };
            const string expectedDigest{ "567f69f168cd7844e65259ce658fe7aadfa25216e68eca0eb7ab8262" };

            Assert::AreEqual(expectedDigest, actualDigest);
        }
        TEST_METHOD(Test_Input_String_empty)
        {
            const string actualDigest{ FkstHashConsole::sha224("") };
            const string expectedDigest{ "d14a028c2a3a2bc9476102bb288234c415a2b01f828ea62ac5b3e42f" };

            Assert::AreEqual(expectedDigest, actualDigest);
        }
    };
}
