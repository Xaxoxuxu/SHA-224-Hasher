/**
 * Digests taken from official specifications and
 * https://tools.ietf.org/html/rfc4634#page-7
 */

#include "pch.h"
#include "CppUnitTest.h"
#include "../sha-224/fkstHashFile.h"
#include <iostream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using std::string;

namespace UnitTests
{
    TEST_CLASS(FkstHashFileTests)
    {
    public:
        TEST_METHOD(Test_Input_FileContent_abc)
        {
            const string actualDigest{ FkstHashFile::sha224("test_abc.txt") };
            const string expectedDigest{ "23097d223405d8228642a477bda255b32aadbce4bda0b3f7e36c9da7" };

            Assert::AreEqual(expectedDigest, actualDigest);
        }

        TEST_METHOD(Test_Input_FileContent_Empty)
        {
            const string actualDigest{ FkstHashFile::sha224("test_empty.txt") };
            const string expectedDigest{ "d14a028c2a3a2bc9476102bb288234c415a2b01f828ea62ac5b3e42f" };

            Assert::AreEqual(expectedDigest, actualDigest);
        }
        TEST_METHOD(Test_Input_FileNotFound)
        {
            bool thrown{ false };

            try
            {
                (void)FkstHashFile::sha224("non-existent-file.test");
            }
            catch (const std::runtime_error&) // ignore exception details
            {
                thrown = true;
            }
            catch (const std::exception&) // ignore exception details
            {
                // handle unexpected exceptions
            }

            Assert::IsTrue(thrown);
        }
    };
}
