#pragma once
#include "Farey_core.h"
#include <vector>

class vec {
public:
	vec(int128_t m = _MOD, int128_t n = _N);
	vec(const std::vector<int128_t>&, int128_t m = _MOD, int128_t n = _N);
	vec(const std::vector<Farey_fraction>&);
	vec(const std::vector<std::string>&, int128_t m = _MOD, int128_t n = _N);
	Farey_fraction& operator [] (size_t);
	//Farey_fraction& operator = (std::string);
	void add(const std::string&, std::istream & = std::cin);
	void read_vec(std::istream& = std::cin);
	void print_vec(std::ostream& = std::cout);
	//const Farey_fraction& operator [](size_t i) const;
	int64_t get_dim() const;
	int128_t get_mod() const;
	int128_t get_N() const;
private:
	int64_t dim;
	int128_t mod;
	int128_t N;
	std::vector<Farey_fraction> v;
};

long double scalar(vec&, vec&);
long double scalar(const std::vector<long double>&, const std::vector<long double>&);