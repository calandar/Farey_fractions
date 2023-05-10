#pragma once
#include "Farey_core.h"
#include <vector>

class vec {
public:
	vec();
	vec(const std::vector<BigInt>&);
	vec(const std::vector<Farey_fraction>&);
	vec(const std::vector<std::string>&);
	Farey_fraction& operator [] (size_t);
	void print_vec(std::ostream& = std::cout);
	//const Farey_fraction& operator [](size_t i) const;
	size_t get_dim() const;
	BigInt get_mod() const;
	BigInt get_N() const;
private:
	size_t dim;
	BigInt mod;
	BigInt N;
	std::vector<Farey_fraction> v;
};

long double scalar(vec&, vec&);