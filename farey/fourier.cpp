#include "fourier.h"
#include <exception>
#include <sstream>
#include <iomanip>
#include <fstream>

std::ofstream ofst("log.txt");

component::component(int128_t m, int128_t n) {
	re = Farey_fraction(m, n, 0, 1);
	im = Farey_fraction(m, n, 0, 1);
}

component::component(const std::string& s, int128_t m, int128_t n) {
	auto res = extract_component(s);
	re = Farey_fraction(m,n,res.first);
	im = Farey_fraction(m,n,res.second);
}

component::component(const std::string& s1, const std::string& s2, int128_t m, int128_t n) {
	re = Farey_fraction(m, n, s1);
	im = Farey_fraction(m, n, s2);
}


component component::operator+(const component& rhs) {
	component res;
	res.re = this->re + rhs.re;
	res.im = this->im + rhs.im;
	return res;
}

component component::operator / (size_t N) {
	component res;
	res.re = this->re / Farey_fraction(_MOD,_N, N, 1);
	res.im = this->im / Farey_fraction(_MOD, _N, N, 1);
	return res;
}

component component::operator*(const component& rhs) {
	component res;
	res.re = this->re * rhs.re - this->im * rhs.im;
	res.im = this->im * rhs.re + this->re * rhs.im;
	return res;
}

std::ostream& operator << (std::ostream& os, const component& c) {
	bool printed = false;
	os << '(' << c.re.to_long_double() << ',' << c.im.to_long_double() << ')';
	return os;
}

samples::samples(int128_t m, int128_t n) {
	mod = m;
	N = n;
	dim = 0;
}

component& samples::operator [] (size_t index) {
	return v[index];
}

samples::samples(const std::vector<std::string>& cont, int128_t m, int128_t n) {
	for (size_t i = 0; i < cont.size(); i++) {
		add(cont[i]);
	}
}

void samples::add(const component& c) {
	v.push_back(c);
	dim++;
}

void samples::add(const std::string& s) {
	v.push_back(component(s));
	dim++;
}

void samples::print(std::ostream& os) const {
	for (size_t i = 0; i < dim; i++) {
		os << v[i] << ' ';
	}
}

int64_t samples::get_dim() const {
	return dim;
}

std::pair<std::string, std::string> extract_component(const std::string& number) { // выделить действительную и мнимую часть из ввода
	bool imagine = false;
	size_t pos = number.rfind('i');
	if (pos != std::string::npos) imagine = true; // есть ли мнимая часть
	std::pair<std::string, std::string> res = { "0", "0" };
	bool minus = false;
	int64_t sign = number.size();
	int64_t j = number.size() - 1; // ищем знак-разделитель. j указывает на знак
	while (j >= 0) {
		if (number[j] == '+' || number[j] == '-') break;
		j--;
	}
	sign = j;	
	if (!(j == -1 || j == 0) || !imagine) { // есть действительная часть
		if (j == 0) sign = number.size();
		std::string re_part = number.substr(0, sign);
		if (re_part == "-0") re_part = "0";
		if (!valid_num(re_part)) throw std::invalid_argument("Real part error");
		res.first = re_part;
	}
	
	if (imagine && pos != number.size() - 1) throw std::invalid_argument("Imaginary unit error");
	if (imagine) {
		if (sign >= 0 && number[sign] == '-') minus = true;
		std::string im_part = number.substr(sign + 1, number.size() - sign - 2);
		if (minus && im_part!="0") im_part = "-" + im_part;
		if (!valid_num(im_part)) throw std::invalid_argument("Imagine part error");
		res.second = im_part;
	}
	
	return res;
}

std::vector<cplx> direct_conversion_classic(const std::vector<long double>& values) {
	std::vector<cplx> res;
	size_t N = values.size();
	for (size_t i = 0; i < N; i++) {
		cplx curr;
		std::stringstream ss1;
		std::stringstream ss2;
		for (size_t j = 0; j < N; j++) {
			long double cs = cos(twoPi * i * j / N);
			//if (abs(cs) < 1e-12) cs = 0.0;
			ss1 << std::setprecision(6) << cs;
			long double sn = -sin(twoPi * i * j / N);
			//if (abs(sn) < 1e-12) sn = 0.0;
			ss2 << std::setprecision(6) << sn;
			cplx tmp(cs, sn);
			curr = curr + values[j] / N * tmp;
		}
		res.push_back(curr);
	}
	return res;
}


std::vector<cplx> inverse_conversion_classic(const std::vector<cplx>& values) {
	std::vector<cplx> res;
	size_t N = values.size();
	for (size_t i = 0; i < N; i++) {
		cplx curr;
		std::stringstream ss1;
		std::stringstream ss2;
		for (size_t j = 0; j < N; j++) {
			long double cs = cos(twoPi * i * j / N);
			//if (abs(cs) < 1e-12) cs = 0.0;
			ss1 << std::setprecision(6) << cs;
			long double sn = sin(twoPi * i * j / N);
			//if (abs(sn) < 1e-12) sn = 0.0;
			ss2 << std::setprecision(6) << sn;
			cplx tmp(cs, sn);
			curr = curr + values[j] * tmp;
		}
		res.push_back(curr);
	}
	return res;
}

samples direct_conversion_alt(const std::vector<std::string>& values) {
	samples res;
	size_t N = values.size();
	for (size_t i = 0; i < N; i++) {
		component curr;
		std::stringstream ss1;
		std::stringstream ss2;
		for (size_t j = 0; j < N; j++) {
			long double cs = cos(twoPi * i * j / N);
			if (abs(cs) < 1e-12) cs = 0.0;
			ss1 << std::setprecision(6) << cs;
			long double sn = -sin(twoPi * i * j / N);
			if (abs(sn) < 1e-12) sn = 0.0;
			ss2 << std::setprecision(6) << sn;
			component tmp(ss1.str(), ss2.str());
			component val(values[j]);
			curr = curr + val * tmp / N;
			ss1.str(std::string()); //clear stringstream
			ss2.str(std::string()); //clear stringstream
		}
		res.add(curr);
	}
	return res;
}

samples inverse_conversion_alt(samples values) {
	samples res;
	size_t N = values.get_dim();
	for (size_t i = 0; i < N; i++) {
		component curr;
		std::stringstream ss1;
		std::stringstream ss2;
		for (size_t j = 0; j < N; j++) {
			long double cs = cos(twoPi * i * j / N);
			if (abs(cs) < 1e-12) cs = 0.0;
			ss1 << std::setprecision(6) << cs;
			long double sn = sin(twoPi * i * j / N);
			if (abs(sn) < 1e-12) sn = 0.0;
			ss2 << std::setprecision(6) << sn;
			component tmp(ss1.str(), ss2.str());
			component val(values[j]);
			ofst << "i = " << i << " | j = " << j << " | Curr before:" << curr << " | val = " << val << " | tmp = " << tmp << std::endl;
			curr = curr + val * tmp;
			ofst << "Curr after: " << curr << /*" Curr.re num: " << curr.re.get_num() <<*/ " | val * tmp = " << val * tmp << "\n";
			/*if (curr.re.get_num() < _N) {
				ofst << "Num is ok\n";
			}
			else {
				ofst << "Num is not ok\n";
			}*/
			ofst << " ----------------------------------------------" << std::endl;
			ss1.str(std::string()); //clear stringstream
			ss2.str(std::string()); //clear stringstream
		}
		res.add(curr);
	}
	return res;
}


Farey_fraction sinP(int num_coef, int denom_coef, int prec) {
	
	num_coef %= denom_coef;
//	long double rads = twoPi / 2 * (num_coef / long double(denom_coef));
	//std::stringstream ss;
//	ss << std::setprecision(20) << rads;
    Farey_fraction twoPi_f = Farey_fraction(_MOD, _N, tP);
	Farey_fraction x = twoPi_f / 2ll * num_coef / denom_coef;
	//Farey_fraction x(_MOD, _N, ss.str());
	Farey_fraction res = x;
	Farey_fraction Minus(_MOD, _N,-1,1);
	for (int index = 3; index < prec; index += 2) {
		res = res + Minus * pow(x, index) / fact(index);
		Minus *= Farey_fraction(_MOD, _N, -1, 1);
	}
	return res;
}

Farey_fraction pow(const Farey_fraction& b, int power) {
	Farey_fraction res(_MOD, _N, 1, 1);

	while (power > 0) {
		res *= b;
		power--;
	}
	std::cout << " pow = " << res;
	return res;
}


Farey_fraction fact(int a) {
	Farey_fraction res(_MOD, _N, 1, 1);

	if (a == 1) {
		return Farey_fraction(_MOD, _N, 1, 1);;
	}
	else {

		res = Farey_fraction(_MOD, _N, a, 1) * fact(a - 1);

	}
	std::cout << " fact = " << res;
	std::cout << std::endl;
	return res;
}