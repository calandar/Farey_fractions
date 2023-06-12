#include "Farey_core.h"
#include "scalar.h"
#include "fourier.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <optional>
#include <sstream>
#include <random>
#include "timer.h"


void read_vector(std::vector<long double>& v, std::istream& is = std::cin) {
	for (size_t i = 0; i < v.size(); i++) {
		is >> v[i];
	}
}

int main() {
	std::string op;
	
	int128_t mod = _MOD, N = _N;
	std::ifstream ifs("input_test.txt");
	std::ofstream ofs("output_test.txt");
	std::optional<std::reference_wrapper<std::ostream>> os;
	std::optional<std::reference_wrapper<std::istream>> is;

	std::cout << "Select problem: \n1 - Scalar product \n2 - Discrete Fourier transform  \n >>>: ";
	std::string prob;
	std::cin >> prob;
	if (prob == "1") {
		std::cout << "Input type: \n1 - Console  \n2 - File  \n3 - Scalar product problem   \n >>>: ";
		std::cin >> op;
		if (op == "1" || op == "2") {
			if (op == "1") {
				os = std::cout;
				is = std::cin;
			}
			else if (op == "2") {
				os = ofs;
				is = ifs;
			}
			vec a(mod, N);
			//a.read_vec(*is);
			int64_t d; // размерность первого вектора
			if (op == "1") std::cout << "Dimentions of vector: ";
			is->get() >> d;
			std::string curr;
			long double ld;
			if (op == "1") std::cout << "Enter values: " << std::endl;
			std::vector<long double> a1;
			for (size_t i = 0; i < d; i++) {
				is->get() >> curr;
				std::stringstream ss(curr);
				a.add(curr);
				ss >> ld;
				a1.push_back(ld);
			}
			vec b(mod, N);
			if (op == "1") std::cout << "Dimentions of vector: ";
			is->get() >> d;
			std::vector<long double> b1;
			if (op == "1") std::cout << "Enter values: " << std::endl;
			for (size_t i = 0; i < d; i++) {
				is->get() >> curr;
				std::stringstream ss(curr);
				b.add(curr);
				ss >> ld;
				b1.push_back(ld);
			}
			long double s1;
			{
				auto t = timer(*os, "Scalar by Farey");
				s1 = scalar(a, b);
			}
			long double s2;
			{
				auto t = timer(*os, "Scalar by double");
				s2 = scalar(a1, b1);
			}
			if (op == "1") std::cout << "Results: " << std::endl;
			os->get() << "Size: " << a.get_dim() << std::endl;
			os->get() << std::setprecision(25) << "Using Farey fractions: " << s1 << std::endl;
			os->get() << std::setprecision(25) << "    Using long double: " << s2 << std::endl;
		}
		else if (op == "3") {
			os = ofs;
			is = ifs;
			for (int i : {-17, -10, -5, 0, 4, 10, 11, 12, 13, 15, 23}) {
				for (int j : {-32, -19, -5, 1, 5, 10, 11, 12, 13, 15, 28}) {
					vec f1(mod, N);
					vec f2(mod, N);
					std::vector<long double> l1;
					std::vector<long double> l2;
					f1.add(pow_10(i));
					l1.push_back(stold(pow_10(i)));
					f1.add("1223");
					l1.push_back(1223);
					f1.add(pow_10(i - 1));
					l1.push_back(stold(pow_10(i - 1)));
					f1.add(pow_10(i - 2));
					l1.push_back(stold(pow_10(i - 2)));
					f1.add("3");
					l1.push_back(3);
					f1.add("-" + pow_10(i - 5));
					l1.push_back(stold("-" + pow_10(i - 5)));

					f2.add(pow_10(j));
					l2.push_back(stold(pow_10(j)));
					f2.add("2");
					l2.push_back(2);
					f2.add("-" + pow_10(j + 1));
					l2.push_back(stold("-" + pow_10(j + 1)));
					f2.add(pow_10(j));
					l2.push_back(stold(pow_10(j)));
					f2.add("2111");
					l2.push_back(2111);
					f2.add(pow_10(j + 3));
					l2.push_back(stold(pow_10(j + 3)));

					std::cout << "Alpha = " << i << ", Beta = " << j << std::endl;
					long double s1;
					{
						auto t = timer(*os, "Scalar by Farey");
						s1 = scalar(f1, f2);
					}
					long double s2;
					{
						auto t = timer(*os, "Scalar by double");
						s2 = scalar(l1, l2);
					}
					std::cout << "-------------------------------------" << std::endl;
					os->get() << "Alpha = " << i << ", Beta = " << j << std::endl;
					os->get() << std::setprecision(15) << "Using Farey fractions: " << s1 << std::endl;
					os->get() << std::setprecision(15) << "    Using long double: " << s2 << std::endl;
					os->get() << "--------------------------" << std::endl;
				}
			}
		}
	}
	else if (prob == "2"){
		std::cout << "Input type: \n1 - Console  \n2 - File  \n3 - Scalar product problem   \n >>>: "; //????????????
		std::cin >> op;
		
		os = ofs;
		is = ifs;//!!!!

		std::vector<long double> vals;
		std::vector<std::string> samp;
		size_t n = 0;
		is->get() >> n;
		std::string curr;
		long double ld;
		os->get() << "Input:\n";
		for (size_t i = 0; i < n; i++) {
			is->get() >> curr;
			std::stringstream ss(curr);
			samp.push_back(curr);
			ss >> ld;
			vals.push_back(ld);
			os->get() << ld << ' ';
		}
		os->get() << std::endl;
		os->get() << std::endl;

		//===========================================================================
		//блок прямого
		os->get() << "Using long double: " << std::endl;
		std::vector<cplx> ans;
		{
			auto t = timer(*os, "Direct transform by double");
			ans = direct_conversion_classic(vals);
		}

		os->get() << "Direct transform:" << std::endl;
		for (auto x : ans) {
			os->get() << x << ' ';
		}
		os->get() << std::endl;
		os->get() << std::endl;
		//===========================================================================
		//блок обратного
		std::vector<cplx> rev;
		{
			auto t = timer(*os, "Inverse transform by double");
			rev = inverse_conversion_classic(ans);
		}
		
		os->get() << "Inverse transform:" << std::endl;
		for (auto x : rev) {
			os->get() << x << ' ';
		}
		os->get() << std::endl;
		os->get() << std::endl;
		
		//===========================================================================
		//блок прямого
		os->get() << "Using Farey fractions: " << std::endl;
		samples rs;
		{
			auto t = timer(*os, "Direct transform by Farey");
			rs = direct_conversion_alt(samp);
		}

		os->get() << "Direct transform:" << std::endl;
		rs.print(*os);
		os->get() << std::endl;
		os->get() << std::endl;
		
		//===========================================================================
		//блок обратного
		os->get() << "Inverse transform:" << std::endl;
		samples inv;
		{
			auto t = timer(*os, "Inverse transform by Farey");
			inv = inverse_conversion_alt(rs);
		}
		inv.print(*os);

		//===========================================================================
		//дельты
		os->get() << "\n\nDelta double: \n";
		for (int i = 0; i < rev.size(); ++i) {
			os->get() << abs(rev[i] - vals[i]) / abs(vals[i]) << ' ';
		}
		os->get() << std::endl;

		os->get() << "Delta Farey: \n";
		for (int i = 0; i < inv.get_dim(); ++i) {
			os->get() << abs(inv[i].re.to_long_double() - vals[i]) / abs(vals[i]) << ' ';
		}
		os->get() << std::endl;

	}
	else {
	using namespace std;
		std::cout << "Problem not found. Exitting...\n";
		
		
			component tmp{ "1"s, "0"s };
			component val{ "36954.8"s, "0"s };

			component curr{ "0"s, "0"s };
			std::cout << curr.re.get_num() << '\n';
			auto res = val * tmp;
			curr = curr + res;

			//std::cout << res1 << ' ' << curr << '\n';

			std::cout << res.re.get_num() << ' ' << curr.re.get_num() << '\n';

	}
	return 0;
}

//int main() {
//	Farey_fraction a1(_MOD, _N, 5, 2);
//	Farey_fraction a2(_MOD, _N, 8, 19);
//	Farey_fraction a12 = a1 + a2;
//	std::cout << a12 << std::endl;
//	std::cout << a12.to_long_double() << std::endl;
//
//
//}