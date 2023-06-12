//#include "pch.h"
#include "CppUnitTest.h"
#include "../farey/Farey_core.h"
#include "../farey/Farey_core.cpp"
#include "../farey/scalar.h"
#include "../farey/scalar.cpp"
#include "../farey/fourier.h"
#include "../farey/fourier.cpp"


using namespace std;


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
			Farey_fraction f2(_MOD, _N, "1.4"s);
			Assert::IsTrue(f2.get_numerator() == 14 && f2.get_denominator() == 10, L"1");
			Farey_fraction f3(_MOD, _N, "123.0"s);
			Assert::IsTrue(f3.get_numerator() == 123 && f3.get_denominator() == 1, L"2");
			Farey_fraction f5(_MOD, _N, "-2.0"s);
			Assert::IsTrue(f5.get_numerator() == -2 && f5.get_denominator() == 1, L"3");
			Farey_fraction f7(_MOD, _N, "0"s);
			Assert::IsTrue(f7.get_numerator() == 0 && f7.get_denominator() == 1, L"4");
			Farey_fraction f8(_MOD, _N, "-5"s);
			Assert::IsTrue(f8.get_numerator() == -5 && f8.get_denominator() == 1, L"5");
			Farey_fraction f11(_MOD, _N, "-0.35"s);
			Assert::IsTrue(f11.get_numerator() == -35 && f11.get_denominator() == 100, L"6");
			Farey_fraction f12(_MOD, _N, "-0.0041"s);
			Assert::IsTrue(f12.get_numerator() == -41 && f12.get_denominator() == 10000, L"7");
			Farey_fraction f13(_MOD, _N, "-4.01"s);
			Assert::IsTrue(f13.get_numerator() == -401 && f13.get_denominator() == 100, L"8");
			Farey_fraction ff2(_MOD, _N, "-0.0001"s);
			Assert::IsTrue(ff2.get_numerator() == -1 && ff2.get_denominator() == 10000, L"9");
			Farey_fraction f15(_MOD, _N, "990.000"s);
			Assert::IsTrue(f15.get_numerator() == 990 && f15.get_denominator() == 1, L"10");
			Farey_fraction f16(_MOD, _N, "-0.1959200000"s);
			Assert::IsTrue(f16.get_numerator() == -19592 && f16.get_denominator() == 100000, L"11");
		}

		TEST_METHOD(Farey_core_big_nums) {
			Farey_fraction bg1(_MOD, _N, "4178898285647891289018422312"s);
			int128_t ans1 = int128_t("4178898285647891289018422312");
			Assert::IsTrue(bg1.get_numerator() == ans1 && bg1.get_denominator() == 1, L"1");



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

			Farey_fraction sub5(_MOD, _N, 4);
			Farey_fraction sub6(_MOD, _N, 9);
			Farey_fraction sub56 = sub5 - sub6;
			Assert::IsTrue(sub56.get_num() == _MOD - 5, L"3");



		}
		
		TEST_METHOD(Farey_core_multiply) {
			Farey_fraction mul1(_MOD, _N, 5, 2);
			Farey_fraction mul2(_MOD, _N, 13, 6);
			Farey_fraction mul12 = mul1 * mul2;
			Assert::IsTrue(mul12.get_numerator() == 65 && mul12.get_denominator() == 12, L"1");

			Farey_fraction mul3(_MOD, _N, _MOD/2 + 1);
			Farey_fraction mul4(_MOD, _N, 2);
			Farey_fraction mul34 = mul3 * mul4;
			Assert::IsTrue(mul34.get_num() == 1,  L"2");

			Farey_fraction mul5(_MOD, _N, _MOD - 1);
			Farey_fraction mul6(_MOD, _N, _MOD - 1);
			Farey_fraction mul56 = mul5 * mul6;
			Assert::IsTrue(mul56.get_num() == 1, L"2");
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

		TEST_METHOD(Farey_core_assignment) {
			Farey_fraction ass1(_MOD, _N, 5, 2);
			ass1 = "1.5";
			Assert::IsTrue(ass1.get_numerator() == 15 && ass1.get_denominator() == 10, L"1");
			Farey_fraction ass2(_MOD, _N, 1, 10);
			ass2 = "0";
			Assert::IsTrue(ass2.get_numerator() == 0 && ass2.get_denominator() == 1, L"2");
		}

		TEST_METHOD(Farey_core_any) {
			Farey_fraction fir(_MOD, _N, 5, 2);
			Farey_fraction sec(_MOD, _N, 10, 4);
			Assert::IsTrue(fir.get_num() == sec.get_num(), L"1");

			Farey_fraction mul1(_MOD, _N, 5, 2);
			Farey_fraction mul2(_MOD, _N, 3, 4);
			Farey_fraction mul3(_MOD, _N, 3, 4);
			Farey_fraction mul4(_MOD, _N, 7, 2);
			auto res = mul1 * mul2 - mul3 * mul4;
			Assert::IsTrue(res.get_numerator() == -3 && res.get_denominator() == 4, L"2");
		}

		TEST_METHOD(Component) {
			component val{-9238.7, -6712.32};
			component tmp{ 0.309017, 0.951057 };
			auto res = val * tmp;
			
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
			Assert::IsTrue(valid_num("1.25"), L"1.25");
			Assert::IsTrue(valid_num("-0.01"), L"-0.01");
		}

		TEST_METHOD(ZExtract_component) {
			auto p1 = extract_component("-123.5-0.87i");
			Assert::IsTrue(p1.first == "-123.5" && p1.second == "-0.87", L"1");
			auto p2 = extract_component("900");
			Assert::IsTrue(p2.first == "900" && p2.second == "0", L"2");
			auto p3 = extract_component("-1.502i");
			Assert::IsTrue(p3.first == "0" && p3.second == "-1.502", L"3");
			auto p4 = extract_component("205.103i");
			Assert::IsTrue(p4.first == "0" && p4.second == "205.103", L"4");
			auto p5 = extract_component("12+5i");
			Assert::IsTrue(p5.first == "12" && p5.second == "5", L"5");
			auto p6 = extract_component("0-0i");
			Assert::IsTrue(p6.first == "0" && p6.second == "0", L"6");
			auto p7 = extract_component("-935");
			Assert::IsTrue(p7.first == "-935" && p7.second == "0", L"7");
			auto p8 = extract_component("-0.38738+13.578i");
			Assert::IsTrue(p8.first == "-0.38738" && p8.second == "13.578", L"8");
			auto p9 = extract_component("381.93");
			Assert::IsTrue(p9.first == "381.93" && p9.second == "0", L"9");
		}

	};
}
