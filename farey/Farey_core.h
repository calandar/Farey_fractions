#pragma once
#include <iostream>
#include "uintwide_t.h"


using int128_t = ::math::wide_integer::uintwide_t<256, std::uint32_t, void, true>;
//using int256_t = ::math::wide_integer::uintwide_t<256, std::uint32_t, void, true>;


// ========= Значения параметров по умолчанию ========= //

const int128_t _MOD = int128_t("170141183460469231731687303715884105703");
const int128_t _N = int128_t(9223372036854775807);
//const int128_t _MOD = int128_t("57896044618658097711785492504343953926634992332820282019728792003956564819949"); //256
//const int128_t _N = int128_t("170141183460469231731687303715884105727");
//const int128_t _MOD = int128_t("6703903964971298549787012499102923063739682910296196688861780721860882015036773488400937149083451713845015929093243025426876941405973284973216824503041861");
//const int128_t _N = int128_t("57896044618658097711785492504343953926634992332820282019728792003956564819967");  //512
//const int128_t _MOD = int128_t("89884656743115795386465259539451236680898848947115328636715040578866337902750481566354238661203768010560056939935696678829394884407208311246423715319737062188883946712432742638151109800623047059726541476042502884419075341171231440736956555270413618581675255342293149119973622969239858152417678164812112068247");
//const int128_t _N = int128_t("6703903964971298549787012499102923063739682910296196688861780721860882015036773488400937149083451713845015929093243025426876941405973284973216824503042047"); 
//#define _MOD 9223372036854775783
//#define _N 2147483647


class Farey_fraction {
public:
	// ========= Конструкторы ========= //
	Farey_fraction();
	Farey_fraction(int128_t, int128_t, int128_t);
	Farey_fraction(int128_t, int128_t, int128_t, int128_t);
	Farey_fraction(int128_t, int128_t, std::string);	
	Farey_fraction(int128_t, int128_t, std::string,int,int);	
	// ========= Перегруженные арифметические операторы ========= //
	Farey_fraction operator +   (const Farey_fraction&);
	Farey_fraction operator +   (int64_t);
	Farey_fraction operator -   (const Farey_fraction&);
	Farey_fraction operator -   (int64_t);
	Farey_fraction operator *   (const Farey_fraction&);
	Farey_fraction operator *   (int64_t);
//	const Farey_fraction operator *   (const Farey_fraction&) const;
	Farey_fraction operator /   (const Farey_fraction&);
	Farey_fraction operator /   (int64_t);
	Farey_fraction operator =  (const Farey_fraction&);
	Farey_fraction operator =  (const std::string&);
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


bool valid_num(const std::string& s);	// Проверка, является ли строка подходящей в качестве вещественного значения
bool no_overflow(int128_t, int128_t);   // Проверка на переполнение операции сложения
int128_t  safe_mul(int128_t, int128_t, int128_t); // Безопасное сложение - без переполнений
void strip_leading_zeroes(std::string&); // Удалить ведущие нули
std::string pow_10(int sze); // создать степень десяти
