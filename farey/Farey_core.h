#pragma once
//#include <cstdint>
#include <iostream>
#include "BigInt.h"

//BigInt inverse_modulo(BigInt num, BigInt mod); // используем малую теорему Ферма для нахождения обратного числа
//BigInt bin_pow(BigInt a, uint64_t n, uint64_t mod); // бинарное возведение в степень



class Farey_fraction {
public:
	Farey_fraction();
	Farey_fraction(BigInt m, BigInt n, BigInt number);
	Farey_fraction(BigInt m, BigInt n, BigInt num, BigInt denom);
	Farey_fraction& operator + (const Farey_fraction& rhs);
	Farey_fraction& operator - (const Farey_fraction& rhs);
	Farey_fraction& operator * (const Farey_fraction& rhs);
	Farey_fraction& operator / (const Farey_fraction& rhs);
	BigInt get_numerator() const;
	BigInt get_denominator() const;
	BigInt get_num() const;
private:
	BigInt numerator;  // Числитель дроби Фарея
	BigInt denominator; // Знаменитель дроби Фарея
	BigInt mod; // Модуль
	BigInt N; // Порядок дроби Фарея
	BigInt num; // Число в модулярной арифметике, соответствующее дроби Фарея
	void calc();
	void Normalize();
	void reverse_calc();   // найти дробь по num с помощью расширенного алгоритма Евклида
	Farey_fraction swapped(const Farey_fraction& f);
	
};

std::ostream& operator << (std::ostream& os, const Farey_fraction& f);