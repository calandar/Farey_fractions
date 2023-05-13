#include "Farey_core.h"
#include "scalar.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <optional>
#include <sstream>
#include <random>


void read_vector(std::vector<long double>& v, std::istream& is = std::cin) {
	for (size_t i = 0; i < v.size(); i++) {
		is >> v[i];
	}
}

int main() {
	std::string op;
	std::cout << "Desirable precision: ";
	BigInt mod, N;
	int prec;
	std::cin >> prec;
	std::cout << "Farey fraction parameters: \n1 - Default (20 signs)  \n2 - Default (30 signs) \n3 - Set parameters  \n >>>: ";
	int params;
	std::cin >> params;
	if (params == 1) {
		mod = _MOD;
		N = _N;
		std::cout << "MOD = " << mod << std::endl;
		std::cout << "N = " << N << std::endl;
	}
	else if (params == 2) {
		mod = _MOD2;
		N = _N2;
		std::cout << "MOD = " << mod << std::endl;
		std::cout << "N = " << N << std::endl;
	}
	else if (params == 3) {
		std::cout << "MOD = ";
		std::cin >> mod;
		std::cout << "N = ";
		std::cin >> N;
	}
	else {
		std::cout << "Unknown command. Exitting..." << std::endl;
		return -1;
	}
	std::cout << "Input type: \n1 - Console  \n2 - File  \n3 - Random generator (using file)   \n >>>: ";
	std::ifstream ifs("input_test.txt");
	std::ofstream ofs("output_test.txt");
	std::optional<std::reference_wrapper<std::ostream>> os;
	std::optional<std::reference_wrapper<std::istream>> is;
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
		vec a(mod,N);
		//a.read_vec(*is);
		int64_t d; // размерность первого вектора
		is->get() >> d;
		std::string curr;
		long double ld;
		std::vector<long double> a1(d);
		for (size_t i = 0; i < d; i++) {
			is->get() >> curr;
			std::stringstream ss(curr);
			a.add(curr, *is);
			ss >> ld;
			a1.push_back(ld);
		}
		vec b(mod, N);
		is->get() >> d;
		std::vector<long double> b1(d);
		for (size_t i = 0; i < d; i++) {
			is->get() >> curr;
			std::stringstream ss(curr);
			b.add(curr, *is);
			ss >> ld;
			b1.push_back(ld);
		}
		os->get() << std::setprecision(prec) << "Using Farey fractions: " << scalar(a, b) << std::endl;
		os->get() << std::setprecision(prec) << "Using long double: " << scalar(a1, b1) << std::endl;
	}
	else {
		os = ofs;
		is = ifs;
		long double low = -1;
		long double high = 1;
		std::uniform_real_distribution<long double> unif(low, high); // Используем генератор случайных чисел из стандартной библиотеки
		std::default_random_engine re;
		//int n = 100;
		std::cout << "Amount of values to generate: ";
		int n;
		std::cin >> n;
		std::ostringstream ss;
		os->get() << "Values: \n";
		std::vector<std::string> fracs1,fracs2;
		std::vector<long double> doubles1,doubles2;
		long double val;
		os->get() << "First vector	  Second vector\n";
		for (size_t i = 0; i < n; i++) {
			val = unif(re);
			doubles1.push_back(val);
			os->get() << std::setprecision(prec) << val << "     ";
			ss << std::setprecision(prec) << val;
			fracs1.push_back(ss.str());
			ss.str(std::string()); // clear the stream
			val = unif(re);
			doubles2.push_back(val);
			os->get() << std::setprecision(prec) << val << std::endl;
			ss << std::setprecision(prec) << val;
			fracs2.push_back(ss.str());
			ss.str(std::string()); // clear the stream
		}
		vec a(fracs1, mod,N);
		vec b(fracs2, mod,N);
		os->get() << std::setprecision(prec) << "Using Farey fractions: " << scalar(a, b) << std::endl;
		os->get() << std::setprecision(prec) << "Using long double: " << scalar(doubles1, doubles2) << std::endl;
	}

	return 0;
}