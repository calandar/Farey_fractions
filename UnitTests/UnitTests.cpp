//#include "pch.h"
#include "CppUnitTest.h"
#include "../farey/Farey_core.h"
#include "../farey/Farey_core.cpp"
#include "../farey/BigInt.h"
#include "../farey/BigInt.cpp"
#include "../farey/scalar.h"
#include "../farey/scalar.cpp"



using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(Farey_core_tests)
	{
	public:
		
		TEST_METHOD(Valid_number)
		{
			Assert::IsTrue(valid_num("12784.243634"), L"12784.243634");
			Assert::IsTrue(valid_num("-12784.0"), L"-12784.0");
			Assert::IsTrue(valid_num("1.2"), L"1.2");
			Assert::IsTrue(valid_num("101234995.349572598147895706543851351436751368342875137142340398765"), L"101234995.349572598147895706543851351436751368342875137142340398765");
			Assert::IsTrue(valid_num("-342645276234532723745253462552.12433246423432643264352378"), L"-342645276234532723745253462552.12433246423432643264352378");
			Assert::IsTrue(valid_num("82345728923"), L"82345728923");
			Assert::IsFalse(valid_num("-8-2345728923"), L"-8-2345728923");
			Assert::IsTrue(valid_num("-1"), L"-1");
			Assert::IsFalse(valid_num("2345.123."), L"2345.123.");
			Assert::IsFalse(valid_num("82345728923."), L"82345728923.");
			Assert::IsFalse(valid_num("134-"), L"134-");
			Assert::IsFalse(valid_num("123.30.0"), L"123.30.0");
			Assert::IsTrue(valid_num("10"), L"10");
			Assert::IsTrue(valid_num("0"), L"0");
		}
		TEST_METHOD(Constructor_from_double) {
			Farey_fraction f1(TEST_MOD, TEST_N, "123.456");
			Assert::IsTrue(f1.get_numerator() == "123456"_bg && f1.get_denominator() == "1000"_bg, L"1");
			Farey_fraction f2(TEST_MOD, TEST_N, "1.4");
			Assert::IsTrue(f2.get_numerator() == "14"_bg && f2.get_denominator() == "10"_bg, L"2");
			Farey_fraction f3(TEST_MOD, TEST_N, "123.0");
			Assert::IsTrue(f3.get_numerator() == "123"_bg && f3.get_denominator() == "1"_bg, L"3");
			Farey_fraction f4(TEST_MOD, TEST_N, "-123.54");
			Assert::IsTrue(f4.get_numerator() == "-12354"_bg && f4.get_denominator() == "100"_bg, L"4");
			Farey_fraction f5(TEST_MOD, TEST_N, "-2.0");
			Assert::IsTrue(f5.get_numerator() == "-2"_bg && f5.get_denominator() == "1"_bg, L"5");
			Farey_fraction f6(TEST_MOD, TEST_N, "435.14583618400000000");
			Assert::IsTrue(f6.get_numerator() == "435145836184"_bg && f6.get_denominator() == "1000000000"_bg, L"6");
			Farey_fraction f7(TEST_MOD, TEST_N, "0");
			Assert::IsTrue(f7.get_numerator() == "0"_bg && f7.get_denominator() == "1"_bg, L"7");
			Farey_fraction f8(TEST_MOD, TEST_N, "-5");
			Assert::IsTrue(f8.get_numerator() == "-5"_bg && f8.get_denominator() == "1"_bg, L"8");
			Farey_fraction f9(TEST_MOD, TEST_N, "0.4356236");
			Assert::IsTrue(f9.get_numerator() == "4356236"_bg && f9.get_denominator() == "10000000"_bg, L"9");
			Farey_fraction f10(TEST_MOD, TEST_N, "0.0002579");
			Assert::IsTrue(f10.get_numerator() == "2579"_bg && f10.get_denominator() == "10000000"_bg, L"10");
			Farey_fraction f11(TEST_MOD, TEST_N, "-0.35");
			Assert::IsTrue(f11.get_numerator() == "-35"_bg && f11.get_denominator() == "100"_bg, L"11");
			Farey_fraction f12(TEST_MOD, TEST_N, "-0.0041");
			Assert::IsTrue(f12.get_numerator() == "-41"_bg && f12.get_denominator() == "10000"_bg, L"12");
			Farey_fraction f13(TEST_MOD, TEST_N, "-43.0001");
			Assert::IsTrue(f13.get_numerator() == "-430001"_bg && f13.get_denominator() == "10000"_bg, L"13");
		}
	};


}
