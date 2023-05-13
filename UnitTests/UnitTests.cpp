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

	TEST_CLASS(Farey_constructors) {
		TEST_METHOD(Constructor_default) {
			Farey_fraction fr1;
			Assert::IsTrue(fr1.get_numerator() == "0"_bg && fr1.get_denominator() == "1"_bg, L"1");
		}

		TEST_METHOD(Constructor_from_fraction) {
			Farey_fraction fr1(_MOD, _N, "123"_bg, "100"_bg);
			Assert::IsTrue(fr1.get_numerator() == "123"_bg && fr1.get_denominator() == "100"_bg, L"1");
		}


		TEST_METHOD(Constructor_from_double) {
			Farey_fraction f1(_MOD, _N, "123.456");
			Assert::IsTrue(f1.get_numerator() == "123456"_bg && f1.get_denominator() == "1000"_bg, L"1");
			Farey_fraction f2(_MOD, _N, "1.4");
			Assert::IsTrue(f2.get_numerator() == "14"_bg && f2.get_denominator() == "10"_bg, L"2");
			Farey_fraction f3(_MOD, _N, "123.0");
			Assert::IsTrue(f3.get_numerator() == "123"_bg && f3.get_denominator() == "1"_bg, L"3");
			Farey_fraction f4(_MOD, _N, "-123.54");
			Assert::IsTrue(f4.get_numerator() == "-12354"_bg && f4.get_denominator() == "100"_bg, L"4");
			Farey_fraction f5(_MOD, _N, "-2.0");
			Assert::IsTrue(f5.get_numerator() == "-2"_bg && f5.get_denominator() == "1"_bg, L"5");
			Farey_fraction f6(_MOD, _N, "435.14583618400000000");
			Assert::IsTrue(f6.get_numerator() == "435145836184"_bg && f6.get_denominator() == "1000000000"_bg, L"6");
			Farey_fraction f7(_MOD, _N, "0");
			Assert::IsTrue(f7.get_numerator() == "0"_bg && f7.get_denominator() == "1"_bg, L"7");
			Farey_fraction f8(_MOD, _N, "-5");
			Assert::IsTrue(f8.get_numerator() == "-5"_bg && f8.get_denominator() == "1"_bg, L"8");
			Farey_fraction f9(_MOD, _N, "0.4356236");
			Assert::IsTrue(f9.get_numerator() == "4356236"_bg && f9.get_denominator() == "10000000"_bg, L"9");
			Farey_fraction f10(_MOD, _N, "0.0002579");
			Assert::IsTrue(f10.get_numerator() == "2579"_bg && f10.get_denominator() == "10000000"_bg, L"10");
			Farey_fraction f11(_MOD, _N, "-0.35");
			Assert::IsTrue(f11.get_numerator() == "-35"_bg && f11.get_denominator() == "100"_bg, L"11");
			Farey_fraction f12(_MOD, _N, "-0.0041");
			Assert::IsTrue(f12.get_numerator() == "-41"_bg && f12.get_denominator() == "10000"_bg, L"12");
			Farey_fraction f13(_MOD, _N, "-43.0001");
			Assert::IsTrue(f13.get_numerator() == "-430001"_bg && f13.get_denominator() == "10000"_bg, L"13");
		}
	};

	TEST_CLASS(Farey_core_operations)
	{
	public:
		
		TEST_METHOD(Simplify) {
			Farey_fraction s1(_MOD, _N, "100.25", true);
			Assert::IsTrue(s1.get_numerator() == "401"_bg && s1.get_denominator() == "4"_bg, L"1");
			Farey_fraction s2(_MOD, _N, "-0.125", true);
			Assert::IsTrue(s2.get_numerator() == "-1"_bg && s2.get_denominator() == "8"_bg, L"1");
			Farey_fraction s3(_MOD, _N, "17.17", true);
			Assert::IsTrue(s3.get_numerator() == "1717"_bg && s3.get_denominator() == "100"_bg, L"1");

		}

		TEST_METHOD(Farey_core_adding) {
			Farey_fraction a1(_MOD, _N, "5"_bg, "2"_bg);
			Farey_fraction a2(_MOD, _N, "8"_bg, "19"_bg);
			Farey_fraction a12 = a1 + a2;
			Assert::IsTrue(a12.get_numerator() == "111"_bg && a12.get_denominator() == "38"_bg, L"1");
			Farey_fraction a3(_MOD, _N, "123"_bg, "100"_bg);
			Farey_fraction a4(_MOD, _N, "97638"_bg, "10000"_bg);
			Farey_fraction a34 = a3 + a4;
			Assert::IsTrue(a34.get_numerator() == "54969"_bg && a34.get_denominator() == "5000"_bg, L"2");
		}

		TEST_METHOD(Farey_core_subtraction) {
			Farey_fraction sub1(_MOD, _N, "5"_bg, "2"_bg);
			Farey_fraction sub2(_MOD, _N, "56"_bg, "10"_bg);
			Farey_fraction sub12 = sub1 - sub2;
			Assert::IsTrue(sub12.get_numerator() == "-31"_bg && sub12.get_denominator() == "10"_bg, L"1");
			Farey_fraction sub3(_MOD, _N, "123"_bg, "100"_bg);
			Farey_fraction sub4(_MOD, _N, "97638"_bg, "10000"_bg);
			Farey_fraction sub34 = sub3 - sub4;
			Assert::IsTrue(sub34.get_numerator() == "-42669"_bg && sub34.get_denominator() == "5000"_bg, L"2");
		}
		
		TEST_METHOD(Farey_core_multiply) {
			Farey_fraction mul1(_MOD, _N, "5"_bg, "2"_bg);
			Farey_fraction mul2(_MOD, _N, "13"_bg, "6"_bg);
			Farey_fraction mul12 = mul1 * mul2;
			Assert::IsTrue(mul12.get_numerator() == "65"_bg && mul12.get_denominator() == "12"_bg, L"1");
		}

		TEST_METHOD(Farey_core_divide) {
			Farey_fraction div1(_MOD, _N, "5"_bg, "2"_bg);
			Farey_fraction div2(_MOD, _N, "13"_bg, "6"_bg);
			Farey_fraction div12 = div1 / div2;
			Assert::IsTrue(div12.get_numerator() == "15"_bg && div12.get_denominator() == "13"_bg, L"1");
			Farey_fraction div3(_MOD, _N, "5000"_bg, "13"_bg);
			Farey_fraction div4(_MOD, _N, "7"_bg, "9"_bg);
			Farey_fraction div34 = div3 / div4;
			Assert::IsTrue(div34.get_numerator() == "45000"_bg && div34.get_denominator() == "91"_bg, L"2");

		}

	};

	TEST_CLASS(Single_functions) {

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

		TEST_METHOD(Check_params) {
			Assert::AreEqual(checkParams("19"_bg, "3"_bg), 1, L"1");
			Assert::AreEqual(checkParams(_MOD, _N), 1, L"2");
			Assert::AreEqual(checkParams(_MOD2, _N2), 1, L"3");
			Assert::AreEqual(checkParams("9999999967"_bg, "70710"_bg), 1, L"4");
			Assert::AreEqual(checkParams("42391158275216203514294433041"_bg, "145587015690301"_bg), 1, L"5");
			Assert::AreEqual(checkParams("4239115827521620351429440"_bg, "145587015690301"_bg), 0, L"6");
			Assert::AreEqual(checkParams("18"_bg, "3"_bg), 0, L"7");
			Assert::AreEqual(checkParams("-1"_bg, "-1"_bg), 0, L"8");
			Assert::AreEqual(checkParams("1"_bg, "1"_bg), 0, L"9");
		}


	};
}
