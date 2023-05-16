//#include "pch.h"
#include "CppUnitTest.h"
#include "../farey/Farey_core.h"
#include "../farey/Farey_core.cpp"
#include "../farey/scalar.h"
#include "../farey/scalar.cpp"



using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{

	TEST_CLASS(Farey_constructors) {
		TEST_METHOD(Constructor_default) {
			Farey_fraction fr1;
			Assert::IsTrue(fr1.get_numerator() == 0 && fr1.get_denominator() == 1, L"1");
		}

		TEST_METHOD(Constructor_from_fraction) {
			Farey_fraction fr1(_MOD, _N, 123, 100);
			Assert::IsTrue(fr1.get_numerator() == 123 && fr1.get_denominator() == 100, L"1");
		}


		TEST_METHOD(Constructor_from_double) {
			Farey_fraction f2(_MOD, _N, "1.4");
			Assert::IsTrue(f2.get_numerator() == 14 && f2.get_denominator() == 10, L"1");
			Farey_fraction f3(_MOD, _N, "123.0");
			Assert::IsTrue(f3.get_numerator() == 123 && f3.get_denominator() == 1, L"2");
			Farey_fraction f5(_MOD, _N, "-2.0");
			Assert::IsTrue(f5.get_numerator() == -2 && f5.get_denominator() == 1, L"3");
			Farey_fraction f7(_MOD, _N, "0");
			Assert::IsTrue(f7.get_numerator() == 0 && f7.get_denominator() == 1, L"4");
			Farey_fraction f8(_MOD, _N, "-5");
			Assert::IsTrue(f8.get_numerator() == -5 && f8.get_denominator() == 1, L"5");
			Farey_fraction f11(_MOD, _N, "-0.35");
			Assert::IsTrue(f11.get_numerator() == -35 && f11.get_denominator() == 100, L"6");
			Farey_fraction f12(_MOD, _N, "-0.0041");
			Assert::IsTrue(f12.get_numerator() == -41 && f12.get_denominator() == 10000, L"7");
			Farey_fraction f13(_MOD, _N, "-4.01");
			Assert::IsTrue(f13.get_numerator() == -401 && f13.get_denominator() == 100, L"8");
			Farey_fraction ff2(_MOD, _N, "-0.0001");
			Assert::IsTrue(ff2.get_numerator() == -1 && ff2.get_denominator() == 10000, L"9");
			Farey_fraction f15(_MOD, _N, "990.000");
			Assert::IsTrue(f15.get_numerator() == 990 && f15.get_denominator() == 1, L"10");
		}
	};

	TEST_CLASS(Farey_core_operations)
	{
	public:

		TEST_METHOD(Farey_core_adding) {
			Farey_fraction a1(_MOD, _N, 5, 2);
			Farey_fraction a2(_MOD, _N, 8, 19);
			Farey_fraction a12 = a1 + a2;
			Assert::IsTrue(a12.get_numerator() == 111 && a12.get_denominator() == 38, L"1");
			Farey_fraction a3(_MOD, _N, 123, 100);
			Farey_fraction a4(_MOD, _N, 97638, 10000);
			Farey_fraction a34 = a3 + a4;
			Assert::IsTrue(a34.get_numerator() == 54969 && a34.get_denominator() == 5000, L"2");
		}

		TEST_METHOD(Farey_core_subtraction) {
			Farey_fraction sub1(_MOD, _N, 5, 2);
			Farey_fraction sub2(_MOD, _N, 56, 10);
			Farey_fraction sub12 = sub1 - sub2;
			Assert::IsTrue(sub12.get_numerator() == -31 && sub12.get_denominator() == 10, L"1");
			Farey_fraction sub3(_MOD, _N, 123, 100);
			Farey_fraction sub4(_MOD, _N, 97638, 10000);
			Farey_fraction sub34 = sub3 - sub4;
			Assert::IsTrue(sub34.get_numerator() == -42669 && sub34.get_denominator() == 5000, L"2");
		}
		
		TEST_METHOD(Farey_core_multiply) {
			Farey_fraction mul1(_MOD, _N, 5, 2);
			Farey_fraction mul2(_MOD, _N, 13, 6);
			Farey_fraction mul12 = mul1 * mul2;
			Assert::IsTrue(mul12.get_numerator() == 65 && mul12.get_denominator() == 12, L"1");
		}

		TEST_METHOD(Farey_core_divide) {
			Farey_fraction div1(_MOD, _N, 5, 2);
			Farey_fraction div2(_MOD, _N, 13, 6);
			Farey_fraction div12 = div1 / div2;
			Assert::IsTrue(div12.get_numerator() == 15 && div12.get_denominator() == 13, L"1");
			Farey_fraction div3(_MOD, _N, 5000, 13);
			Farey_fraction div4(_MOD, _N, 7, 9);
			Farey_fraction div34 = div3 / div4;
			Assert::IsTrue(div34.get_numerator() == 45000 && div34.get_denominator() == 91, L"2");

		}

	};

	TEST_CLASS(Single_functions) {

		TEST_METHOD(Valid_number)
		{
			Assert::IsFalse(valid_num("12784.243634"), L"12784.243634");
			Assert::IsTrue(valid_num("-12784.0"), L"-12784.0");
			Assert::IsTrue(valid_num("1.2"), L"1.2");
			Assert::IsFalse(valid_num("101234995.349572598147895706543851351436751368342875137142340398765"), L"101234995.349572598147895706543851351436751368342875137142340398765");
			Assert::IsFalse(valid_num("-342645276234532723745253462552.12433246423432643264352378"), L"-342645276234532723745253462552.12433246423432643264352378");
			Assert::IsFalse(valid_num("82345728923"), L"82345728923");
			Assert::IsFalse(valid_num("-8-2345728923"), L"-8-2345728923");
			Assert::IsTrue(valid_num("-1"), L"-1");
			Assert::IsFalse(valid_num("2345.123."), L"2345.123.");
			Assert::IsFalse(valid_num("82345728923."), L"82345728923.");
			Assert::IsFalse(valid_num("134-"), L"134-");
			Assert::IsFalse(valid_num("123.30.0"), L"123.30.0");
			Assert::IsTrue(valid_num("10"), L"10");
			Assert::IsTrue(valid_num("0"), L"0");
			Assert::IsTrue(valid_num("1.25"), L"1.25");
			Assert::IsTrue(valid_num("-0.01"), L"-0.01");
		}

	};
}
