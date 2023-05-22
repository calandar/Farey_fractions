#include "fourier.h"
#include <exception>

component::component(int128_t m, int128_t n) {
	re = Farey_fraction(m, n, 0, 1);
	im = Farey_fraction(m, n, 0, 1);
}

component::component(const std::string& s, int128_t m, int128_t n) {
	auto res = extract_component(s);
	re = Farey_fraction(m,n,res.first);
	im = Farey_fraction(m,n,res.second);
}

component component::operator+(const component& rhs) {
	component res;
	res.re = this->re + rhs.re;
	res.im = this->im + rhs.im;
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
	if (c.re.get_numerator() != 0) {
		os << c.re.to_long_double();
		printed = true;
	}
	if (c.im.get_numerator() != 0) {
		os << c.im.to_long_double() << 'i';
		printed = true;
	}
	if (!printed) os << 0;
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

void samples::add(const std::string& s, std::istream& is) {
	v.push_back(component(s));
	dim++;
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

std::vector<cplx> direct_conversion_classic(const std::vector<long double> values) {
	std::vector<cplx> res;
	size_t N = values.size();
	for (size_t i = 0; i < N; i++) {
		cplx curr;
		for (size_t j = 0; j < N; j++) {
			cplx tmp(cos(twoPi * i * j / N), -sin(twoPi * i * j / N));
			curr = curr + values[j] / N * tmp;
		}
		res.push_back(curr);
	}
	return res;
}


std::vector<cplx> inverse_conversion_classic(const std::vector<cplx> values) {
	std::vector<cplx> res;
	size_t N = values.size();
	for (size_t i = 0; i < N; i++) {
		cplx curr;
		for (size_t j = 0; j < N; j++) {
			cplx tmp(cos(twoPi * i * j / N), sin(twoPi * i * j / N));
			curr = curr + values[j] * tmp;
		}
		res.push_back(curr);
	}
	return res;
}

samples direct_conversion_alt(const std::vector<long double> values) {
	samples res;
	size_t N = values.size();
	for (size_t i = 0; i < N; i++) {
		component curr;
		for (size_t j = 0; j < N; j++) {
			component tmp(cos(twoPi * i * j / N), -sin(twoPi * i * j / N)); // как-то установить точность!!
			curr = curr + values[j] / N * tmp;
		}
		res.push_back(curr);
	}
	return res;
}