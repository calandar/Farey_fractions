#include "scalar.h"
#include <string>
#include <exception>

	vec::vec(int128_t m, int128_t n){
		mod = m;
		N = n;
		dim = 0;
	}
	vec::vec(const std::vector<int128_t>& big_v, int128_t m, int128_t n) {
		mod = m; //.
		N = n; //.
		dim = big_v.size();
		v.resize(dim);
		for (size_t i = 0; i < big_v.size(); i++) {
			v[i] = Farey_fraction(mod, N, big_v[i]);
		}
	}

	vec::vec(const std::vector<Farey_fraction>& big_v) {
		if (big_v.size() == 0) {
			std::cout << "There are no elements in container" << std::endl;
		}
		mod = big_v[0].get_mod(); //.
		N = big_v[0].get_N(); //.
		dim = big_v.size();
		*this = big_v;
	}

	vec::vec(const std::vector<std::string>& double_v, int128_t m, int128_t n) {
		mod = m; // .
		N = n; // .
		dim = double_v.size();
		v.resize(dim);
		for (size_t i = 0; i < double_v.size(); i++) {
			v[i] = Farey_fraction(mod, N, double_v[i]);
		}
	}

	Farey_fraction& vec::operator [](size_t i){
		if (i >= 0 && i < dim) {
			return v[i];
		}
		std::cout << "Index out of range!!" << std::endl;
		exit(228);
	}


	int64_t vec::get_dim() const {
		return dim;
	}

	void vec::add(const std::string& num) {
		//if (valid_num(num)) {
			v.push_back(Farey_fraction(mod, N, num));
			dim++;
		//}
	}

	void vec::read_vec(std::istream& is) {
		v.clear();
		dim = 0;
		int64_t d;
		is >> d;
		if (d <= 0) {
			throw std::length_error("Length must be not less than 1");
		}
		dim = d;
		std::string curr;
		for (size_t i = 0; i < d; i++) {
			is >> curr;
			add(curr);
		}
	}

	void vec::print_vec(std::ostream& os) {
		os << "< ";
		for (size_t i = 0; i < v.size(); i++) {
			os << v[i] << ' ';
		}
		os << '>' << std::endl;
	}

	int128_t vec::get_mod() const {
		return mod;
	}
	int128_t vec::get_N() const {
		return N;
	}

	long double scalar( vec& a,  vec& b) {   
		if (a.get_dim() != b.get_dim()) {
			std::cout << "Dimentions differ" << std::endl;
			throw std::runtime_error("Dimentions differ");
			return 0;
		}
		if (a.get_dim() == 0) {
			std::cout << "Vector has 0 length" << std::endl;
			throw std::runtime_error("Zero length");
			return 0;
		}
		if (a.get_mod() != b.get_mod()) {
			std::cout << "N-order of vectors differ" << std::endl;
			throw std::runtime_error("Farey parameters differ");
			return 0;
		}
		Farey_fraction res = Farey_fraction(a.get_mod(), a.get_N(), 0, 1);
		for (size_t i = 0; i < a.get_dim(); i++) {
			Farey_fraction curr = a[i] * b[i];
			//std::cout << curr << ' ';
			res += curr;
		}
		//std::cout << std::endl;
		//std::cout << res << std::endl; // !!
		return res.to_long_double();
	}

	long double scalar(const std::vector<long double>& v1, const std::vector<long double>& v2) {
		long double res = 0.0;
		for (size_t i = 0; i < v1.size(); i++) {
			long double curr = v1[i] * v2[i];
			res += curr;
			std::cout << curr << ' ';
		}
		std::cout << std::endl;
		return res;
	}

	