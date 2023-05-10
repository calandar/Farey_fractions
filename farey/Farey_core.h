#pragma once
//#include <cstdint>
#include <iostream>
#include "BigInt.h"

//BigInt inverse_modulo(BigInt num, BigInt mod); // ���������� ����� ������� ����� ��� ���������� ��������� �����
//BigInt bin_pow(BigInt a, uint64_t n, uint64_t mod); // �������� ���������� � �������

#define TEST_MOD BigInt("9999999999999999999999999999999999999983")
#define TEST_N BigInt("70710678118654752440")


class Farey_fraction {
public:
	Farey_fraction();
	Farey_fraction(BigInt, BigInt, BigInt);
	Farey_fraction(BigInt, BigInt, BigInt, BigInt);
	Farey_fraction(BigInt, BigInt, std::string);
	Farey_fraction operator +   (const Farey_fraction&);
	Farey_fraction operator -   (const Farey_fraction&);
	Farey_fraction operator *   (const Farey_fraction&);
//	const Farey_fraction operator *   (const Farey_fraction&) const;
	Farey_fraction operator /   (const Farey_fraction&);
	Farey_fraction& operator =  (const Farey_fraction&);
	Farey_fraction& operator += (const Farey_fraction&);
	BigInt get_numerator() const;
	BigInt get_denominator() const;
	BigInt get_num() const;
	BigInt get_mod() const;
	BigInt get_N() const;
	long double to_long_double() const;
private:
	BigInt numerator;  // ��������� ����� �����
	BigInt denominator; // ����������� ����� �����
	BigInt mod; // ������
	BigInt N; // ������� ����� �����
	BigInt num; // ����� � ���������� ����������, ��������������� ����� �����
	void calc();
	void Normalize();
	void reverse_calc();   // ����� ����� �� num � ������� ������������ ��������� �������
	BigInt inverse_modulo(BigInt, BigInt);
	Farey_fraction swapped(const Farey_fraction&);
	
};

std::ostream& operator << (std::ostream& os, const Farey_fraction& f);
bool valid_num(const std::string& s);
BigInt operator "" _bg(const char* str, size_t sze);