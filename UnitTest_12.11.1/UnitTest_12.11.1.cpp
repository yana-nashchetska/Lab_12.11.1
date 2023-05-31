#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab_12.11.1/Lab_12.11.1.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest12111
{
	TEST_CLASS(UnitTest12111)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
            void testInsertNode();
            {
                int expectedAge = 25;
                std::string expectedGender = "man";
                TreeNode* root = nullptr;

                Respondent respondent1;
                respondent1.age = 25;
                respondent1.gender = "man";
                respondent1.education = "primary";
                respondent1.answer = "Yes";
                insertNode(root, respondent1);

           
        

                Assert::AreEqual(expectedAge, respondent1.age);
                Assert::AreEqual(expectedGender, respondent1.gender);

              
             
            }


		}
	};
}
