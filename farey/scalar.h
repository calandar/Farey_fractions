#pragma once
#include "Farey_core.h"
#include <vector>

class vec {
public:
	vec(int64_t m = _MOD, int64_t n = _N);
	vec(const std::vector<int64_t>&, int64_t m = _MOD, int64_t n = _N);
	vec(const std::vector<Farey_fraction>&);
	vec(const std::vector<std::string>&, int64_t m = _MOD, int64_t n = _N);
	Farey_fraction& operator [] (size_t);
	//Farey_fraction& operator = (std::string);
	void add(const std::string&, std::istream & = std::cin);
	void read_vec(std::istream& = std::cin);
	void print_vec(std::ostream& = std::cout);
	//const Farey_fraction& operator [](size_t i) const;
	int64_t get_dim() const;
	int64_t get_mod() const;
	int64_t get_N() const;
private:
	int64_t dim;
	int64_t mod;
	int64_t N;
	std::vector<Farey_fraction> v;
};

long double scalar(vec&, vec&);
long double scalar(const std::vector<long double>&, const std::vector<long double>&);