#pragma once
#include <iostream>


// ========= Значения параметров по умолчанию ========= //
#define _MOD 9223372036854775783
#define _N 2147483647
#define _MOD2 BigInt("999999999999999999999999999999999999999999999999999999999839")
#define _N2 BigInt("707106781186547524400844362104") // для 30 разрядов

class Farey_fraction {
public:
	// ========= Конструкторы ========= //
	Farey_fraction();
	Farey_fraction(int64_t, int64_t, int64_t); 
	Farey_fraction(int64_t, int64_t, int64_t, int64_t);
	Farey_fraction(int64_t, int64_t, std::string);	// REWORKING
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
	int64_t get_numerator() const;
	int64_t get_denominator() const;
	int64_t get_num() const;
	int64_t get_mod() const;
	int64_t get_N() const;
	// ========= Конвертация в long double ========= //
	long double to_long_double() const;
private:
	int64_t numerator{0};  // Числитель дроби Фарея
	int64_t denominator{1}; // Знаменитель дроби Фарея
	int64_t mod{_MOD}; // Модуль
	int64_t N{_N}; // Порядок дроби Фарея
	int64_t num; // Число в модулярной арифметике, соответствующее дроби Фарея
	void calc(); // найти num по дроби Фарея
	void Normalize(); // из минуса к плюсу по модулю.
	void reverse_calc();   // найти дробь по num с помощью расширенного алгоритма Евклида
	int64_t inverse_modulo(int64_t, int64_t); // найти обратное число по модулю с помощью расширенного алгоритма Евклида
	Farey_fraction swapped(const Farey_fraction&); // развернуть дробь Фарея (для деления)
	
};

//bool is_prime(const BigInt& num);
//int checkParams( BigInt& mod,  BigInt& N);  // Проверить, выполняется ли основное условие дробей Фарея
bool valid_num(const std::string& s);	// Проверка, является ли строка подходящей в качестве вещественного значения
bool no_overflow(int64_t, int64_t);
int64_t safe_mul(int64_t, int64_t, int64_t);
void strip_leading_zeroes(std::string&);