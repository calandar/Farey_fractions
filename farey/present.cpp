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

std::ofstream ofst("log.txt");


std::pair<std::vector<cplx>, samples> execute_direct(std::optional<std::reference_wrapper<std::ostream>> os, std::pair<std::vector<long double>, std::vector<std::string>> p, bool round) {
	auto [vals, samp] = p;
	os->get() << "Direct transform:" << std::endl;
	os->get() << "Using long double: " << std::endl;
	std::vector<cplx> ans;
	{
		auto t = timer(ofst, "Direct transform by double");
		ans = direct_conversion_classic(vals);
	}
	if (round)
	for (auto& x : ans) {
		std::stringstream ss1, ss2;
		ss1 << std::setprecision(9) << x.real();
		ss2 << std::setprecision(9) << x.imag();
		x = { stold(ss1.str()), stold(ss2.str()) };
	}

	for (auto x : ans) {
		os->get() << x << ' ';
	}
	os->get() << std::endl;
	os->get() << std::endl;

	os->get() << "Using Farey fractions: " << std::endl;
	samples rs;
	{
		auto t = timer(ofst, "Direct transform by Farey");
		rs = direct_conversion_alt(samp);
	}
	samples rs2;
	if (round)
	for (size_t i = 0; i < rs.get_dim(); i++) {
		std::stringstream ss1, ss2;
		ss1 << std::setprecision(9) << rs[i].re.to_long_double();
		ss2 << std::setprecision(9) << rs[i].im.to_long_double();
		rs2.add(component(ss1.str(), ss2.str()));
	}
	
	rs.print(*os);
	os->get() << std::endl;
	os->get() << std::endl;
	if (round) return { ans, rs2 };
	return { ans,rs };

}


std::pair<std::vector<cplx>, samples> execute_inverse(std::optional<std::reference_wrapper<std::ostream>> os, std::pair<std::vector<cplx>, samples> p) {
	auto [ans, rs] = p;
	os->get() << "Inverse transform:" << std::endl;
	std::vector<cplx> rev;
	{
		auto t = timer(ofst, "Inverse transform by double");
		rev = inverse_conversion_classic(ans);
	}

	os->get() << "Using long double:" << std::endl;
	for (auto x : rev) {
		os->get() << x << ' ';
	}
	os->get() << std::endl;
	os->get() << std::endl;

	os->get() << "Using Farey fractions:" << std::endl;
	samples inv;
	{
		auto t = timer(ofst, "Inverse transform by Farey");
		inv = inverse_conversion_alt(rs);
	}
	inv.print(*os);

	return { rev,inv };
}

void delta(const std::pair<std::vector<long double>, std::vector<std::string>>& direct, const std::pair<std::vector<cplx>, samples>& inverse) {
	auto [vals, samp] = direct;
	auto [rev, inv] = inverse;
	ofst << "Size " << vals.size() << std::endl;
	ofst << "Delta double: \n";
	for (int i = 0; i < rev.size(); ++i) {
		ofst << abs(rev[i] - vals[i]) / abs(vals[i]) << ' ';
	}
	ofst << std::endl;

	ofst << "Delta Farey: \n";
	for (int i = 0; i < inv.get_dim(); ++i) {
		ofst << abs(inv[i].re.to_long_double() - vals[i]) / abs(vals[i]) << ' ';
	}
	ofst << std::endl;
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
				auto t = timer(ofst, "Scalar by Farey");
				s1 = scalar(a, b);
			}
			long double s2;
			{
				auto t = timer(ofst, "Scalar by double");
				s2 = scalar(a1, b1);
			}
			if (op == "1") std::cout << "Results: " << std::endl;
			os->get() << "Size: " << a.get_dim() << std::endl;
			os->get() <<  "Using Farey fractions: " << s1 << std::endl;
			os->get() <<  "    Using long double: " << s2 << std::endl;
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
						auto t = timer(ofst, "Scalar by Farey");
						s1 = scalar(f1, f2);
					}
					long double s2;
					{
						auto t = timer(ofst, "Scalar by double");
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
	else if (prob == "2") {
		std::cout << "Input type: \n1 - Console  \n2 - File  \n >>>: ";
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
			else {
				std::cout << "Wrong command. Exitting...";
				return 0;
			}
		}

		std::cout << "Select action: \n1 - Direct FT  \n2 - Inverse FT  \n3 - Discrete Fourier problem \n >>>: ";
		
		std::string ch = "";
		std::cin >> ch;
		if (ch == "1") {
			std::vector<long double> vals;
			std::vector<std::string> samp;
			size_t n = 0;
			if (op == "1") std::cout << "Enter size: ";
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
				if (op == "2") os->get() << ld << ' ';
			}
			os->get() << std::endl << std::endl;

			auto result = execute_direct(*os, { vals,samp }, false);

		}
		else if (ch == "2") {
			std::vector<cplx> rev;
			samples inv;
			size_t n = 0;
			if (op == "1") {
				os->get() << "Samples size: ";
			}
			is->get() >> n;
			std::string curr;
			for (size_t i = 0; i < n; i++) {
				is->get() >> curr;
				auto num = extract_component(curr);
				rev.push_back({stold(num.first), stold(num.second)});
				inv.add(component(num.first, num.second));
			}
			auto result = execute_inverse(*os, { rev,inv });
		}
		else if (ch == "3") {
			std::vector<long double> vals;
			std::vector<std::string> samp;
			size_t n = 0;
			if (ch == "1") {
				os->get() << "Samples size: ";
			}
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
			os->get() << std::endl << std::endl;

			auto result1 = execute_direct(*os, { vals,samp }, true);

			auto result2 = execute_inverse(*os, result1);

			delta({vals,samp}, result2);
		}
	}
	else {
		std::cout << "Problem not found. Exitting...\n";
		
			//component tmp{ "1"s, "0"s };
			//component val{ "36954.8"s, "0"s };

			//component curr{ "0"s, "0"s };
			//std::cout << curr.re.get_num() << '\n';
			//auto res = val * tmp;
			//curr = curr + res;

			////std::cout << res1 << ' ' << curr << '\n';

			//std::cout << res.re.get_num() << ' ' << curr.re.get_num() << '\n';

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