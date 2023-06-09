#pragma once
#include "Farey_core.h"
#include <vector>
#include <cmath>
#include <complex>

const long double twoPi = 6.2831853071795864769252867665590057683943387987502116419498891846;
const std::string tP = "6.283185307179586476925";


using cplx = std::complex<long double>;


struct component {
	component(int128_t m = _MOD, int128_t n = _N);
	component(const std::string&, int128_t m = _MOD, int128_t n = _N); // из общего вида комплексных чисел
	component(const std::string&, const std::string&, int128_t m = _MOD, int128_t n = _N); // на основе действительной и мнимой части
	component operator + (const component&);
	component operator / (size_t);
	component operator * (const component&);
	Farey_fraction re;
	Farey_fraction im;
};


class samples {
public:
	samples(int128_t m = _MOD, int128_t n = _N);
	samples(const std::vector<std::string>&, int128_t m = _MOD, int128_t n = _N);

	component& operator [] (size_t);
	void add(const component&);
	void add(const std::string&);
	void print(std::ostream& = std::cout) const;
	int64_t get_dim() const;
private:
	int128_t mod;
	int128_t N;
	int64_t dim;
	std::vector<component> v;
	
};

std::pair<std::string, std::string> extract_component(const std::string&);
std::ostream& operator << (std::ostream& os, const component& c);

std::vector<cplx> direct_conversion_classic(const std::vector<long double>& values);
std::vector<cplx> inverse_conversion_classic(const std::vector<cplx>& values);

samples direct_conversion_alt(const std::vector<std::string>& values);
samples inverse_conversion_alt(samples values);

Farey_fraction sinP(int num_coef, int denom_coef, int prec);
Farey_fraction pow(const Farey_fraction& b, int power);
Farey_fraction fact(int a);