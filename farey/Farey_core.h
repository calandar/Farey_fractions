#pragma once
#include <iostream>
#include "uintwide_t.h"


using int128_t = ::math::wide_integer::uintwide_t<128,std::uint32_t,void,true>;

// ========= Значения параметров по умолчанию ========= //

const int128_t _MOD = int128_t("170141183460469231731687303715884105703");
const int128_t _N = int128_t(9223372036854775807);

//#define _MOD 9223372036854775783
//#define _N 2147483647


class Farey_fraction {
public:
	// ========= Конструкторы ========= //
	Farey_fraction();
	Farey_fraction(int128_t, int128_t, int128_t);
	Farey_fraction(int128_t, int128_t, int128_t, int128_t);
	Farey_fraction(int128_t, int128_t, std::string);	// REWORKING
	// ========= Перегруженные арифметические операторы ========= //
	Farey_fraction operator +   (const Farey_fraction&); // REWORKING -- done?
	Farey_fraction operator -   (const Farey_fraction&);
	Farey_fraction operator *   (const Farey_fraction&);
//	const Farey_fraction operator *   (const Farey_fraction&) const;
	Farey_fraction operator /   (const Farey_fraction&);
	Farey_fraction& operator =  (const Farey_fraction&);
	Farey_fraction& operator += (const Farey_fraction&);
	Farey_fraction& operator -= (const Farey_fraction&);
	Farey_fraction& operator *= (const Farey_fraction&);
	Farey_fraction& operator /= (const Farey_fraction&);
	// ========= Операторы ввода/вывода ========= //
	//friend std::istream& operator >> (std::istream& is, Farey_fraction& f);  // оператор ввода для дробей Фарея (impossible?)
    friend std::ostream& operator << (std::ostream& os, const Farey_fraction& f); // оператор вывода для дробей Фарея
	// ========= Методы доступа к полям ========= //
	int128_t get_numerator() const;
	int128_t get_denominator() const;
	int128_t get_num() const;
	int128_t get_mod() const;
	int128_t get_N() const;
	// ========= Конвертация в long double ========= //
	long double to_long_double() const;
private:
	int128_t numerator{0};  // Числитель дроби Фарея
	int128_t denominator{1}; // Знаменитель дроби Фарея
	int128_t mod{_MOD}; // Модуль
	int128_t N{_N}; // Порядок дроби Фарея
	int128_t num; // Число в модулярной арифметике, соответствующее дроби Фарея
	void calc(); // найти num по дроби Фарея
	void Normalize(); // из минуса к плюсу по модулю.
	void reverse_calc();   // найти дробь по num с помощью расширенного алгоритма Евклида
	int128_t inverse_modulo(int128_t, int128_t); // найти обратное число по модулю с помощью расширенного алгоритма Евклида
	Farey_fraction swapped(const Farey_fraction&); // развернуть дробь Фарея (для деления)
	
};

//bool is_prime(const BigInt& num);
//int checkParams( BigInt& mod,  BigInt& N);  // Проверить, выполняется ли основное условие дробей Фарея
bool valid_num(const std::string& s);	// Проверка, является ли строка подходящей в качестве вещественного значения
bool no_overflow(int128_t, int128_t);
int128_t  safe_mul(int128_t, int128_t, int128_t);
void strip_leading_zeroes(std::string&);
//int128_t abs(int128_t);