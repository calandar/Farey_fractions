#pragma once
//#include <cstdint>
#include <iostream>
#include "BigInt.h"

// ========= Значения параметров по умолчанию ========= //
#define _MOD BigInt("9999999999999999999999999999999999999983")
#define _N BigInt("70710678118654752440") // для 20 разрядов
#define _MOD2 BigInt("999999999999999999999999999999999999999999999999999999999839")
#define _N2 BigInt("707106781186547524400844362104") // для 30 разрядов

class Farey_fraction {
public:
	// ========= Конструкторы ========= //
	Farey_fraction();
	Farey_fraction(const BigInt&, const BigInt&, const BigInt&); 
	Farey_fraction(const BigInt&, const BigInt&, const BigInt&, const BigInt&);
	Farey_fraction(const BigInt&, const BigInt&, std::string, bool simplify = false);
	// ========= Перегруженные арифметические операторы ========= //
	Farey_fraction operator +   (const Farey_fraction&);
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
	BigInt get_numerator() const;
	BigInt get_denominator() const;
	BigInt get_num() const;
	BigInt get_mod() const;
	BigInt get_N() const;
	// ========= Конвертация в long double ========= //
	long double to_long_double() const;
private:
	BigInt numerator{0};  // Числитель дроби Фарея
	BigInt denominator{1}; // Знаменитель дроби Фарея
	BigInt mod{_MOD}; // Модуль
	BigInt N{_N}; // Порядок дроби Фарея
	BigInt num; // Число в модулярной арифметике, соответствующее дроби Фарея
	void calc(); // найти num по дроби Фарея
	void Normalize(); // из минуса к плюсу по модулю.
	void reverse_calc();   // найти дробь по num с помощью расширенного алгоритма Евклида
	BigInt inverse_modulo(const BigInt&, const BigInt&); // найти обратное число по модулю с помощью расширенного алгоритма Евклида
	Farey_fraction swapped(const Farey_fraction&); // развернуть дробь Фарея (для деления)
	void throw_if_bad_params(); // выброс исключения при создании дроби с неверными параметрами
	
};

bool is_prime(const BigInt& num);
int checkParams( BigInt& mod,  BigInt& N);  // Проверить, выполняется ли основное условие дробей Фарея
bool valid_num(const std::string& s);	// Проверка, является ли строка подходящей в качестве вещественного значения
BigInt operator "" _bg(const char* str, size_t sze); // Вспомогательный литерал