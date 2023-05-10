#include "scalar.h"
#include <string>


	vec::vec(){}
	vec::vec(const std::vector<BigInt>& big_v) {
		mod = BigInt("9999999999999999999999999999999999999983"); // бпелеммн
		N = BigInt("70710678118654752440");
		dim = big_v.size();
		v.resize(dim);
		for (size_t i = 0; i < big_v.size(); i++) {
			v[i] = Farey_fraction(mod, N, big_v[i]);
		}
	}

	vec::vec(const std::vector<Farey_fraction>& big_v) {
		mod = BigInt("9999999999999999999999999999999999999983"); // бпелеммн
		N = BigInt("70710678118654752440");
		dim = big_v.size();
		v = big_v;
	}

	vec::vec(const std::vector<std::string>& double_v) {
		mod = BigInt("9999999999999999999999999999999999999983"); // бпелеммн
		N = BigInt("70710678118654752440");
		dim = double_v.size();
		v.resize(dim);
		for (size_t i = 0; i < double_v.size(); i++) {
			v[i] = Farey_fraction(mod, N, double_v[i]);
		}
	}

	Farey_fraction& vec::operator [](size_t i){
		if (i >= 0 && i < dim) {
			return  v[i];
		}
		std::cout << "Index out of range!!" << std::endl;
		exit(228);
	}

	//const Farey_fraction& vec::operator [](size_t i) const {
	//	/*if (i >= 0 && i < dim) {
	//		return  v[i];
	//	}
	//	std::cout << "Index out of range!!" << std::endl;
	//	exit(228);*/
	//	return vec::operator [](i);
	//}

	size_t vec::get_dim() const {
		return dim;
	}

	void vec::print_vec(std::ostream& os) {
		os << "< ";
		for (size_t i = 0; i < v.size(); i++) {
			os << v[i] << ", ";
		}
		os << '>' << std::endl;
	}

	BigInt vec::get_mod() const {
		return mod;
	}
	BigInt vec::get_N() const {
		return N;
	}

	long double scalar( vec& a,  vec& b) {   // опнреярхпнбюрэ!!!1!!!!!!1
		if (a.get_dim() != b.get_dim()) {
			std::cout << "Dimentions differ" << std::endl;
			return 0;
		}
		Farey_fraction res(a.get_mod(), a.get_N(), 0ll, 1ll);
		for (size_t i = 0; i < a.get_dim(); i++) {
			Farey_fraction curr = a[i] * b[i];
			res += curr;
		}
		return res.to_long_double();
	}

