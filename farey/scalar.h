#pragma once
#include "Farey_core.h"
#include <vector>

class vec {
public:
	vec(BigInt m = _MOD, BigInt n = _N);
	vec(const std::vector<BigInt>&, BigInt m = _MOD, BigInt n = _N);
	vec(const std::vector<Farey_fraction>&);
	vec(const std::vector<std::string>&, BigInt m = _MOD, BigInt n = _N);
	Farey_fraction& operator [] (size_t);
	//Farey_fraction& operator = (std::string);
	void add(const std::string&, std::istream & = std::cin);
	void read_vec(std::istream& = std::cin);
	void print_vec(std::ostream& = std::cout);
	//const Farey_fraction& operator [](size_t i) const;
	int64_t get_dim() const;
	BigInt get_mod() const;
	BigInt get_N() const;
private:
	int64_t dim;
	BigInt mod;
	BigInt N;
	std::vector<Farey_fraction> v;
};

long double scalar(vec&, vec&);
long double scalar(const std::vector<long double>&, const std::vector<long double>&);