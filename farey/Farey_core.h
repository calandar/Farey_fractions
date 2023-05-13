#pragma once
//#include <cstdint>
#include <iostream>
#include "BigInt.h"

// ========= �������� ���������� �� ��������� ========= //
#define _MOD BigInt("9999999999999999999999999999999999999983")
#define _N BigInt("70710678118654752440") // ��� 20 ��������
#define _MOD2 BigInt("999999999999999999999999999999999999999999999999999999999839")
#define _N2 BigInt("707106781186547524400844362104") // ��� 30 ��������

class Farey_fraction {
public:
	// ========= ������������ ========= //
	Farey_fraction();
	Farey_fraction(const BigInt&, const BigInt&, const BigInt&); 
	Farey_fraction(const BigInt&, const BigInt&, const BigInt&, const BigInt&);
	Farey_fraction(const BigInt&, const BigInt&, std::string, bool simplify = false);
	// ========= ������������� �������������� ��������� ========= //
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
	// ========= ��������� �����/������ ========= //
	//friend std::istream& operator >> (std::istream& is, Farey_fraction& f);  // �������� ����� ��� ������ ����� (impossible?)
    friend std::ostream& operator << (std::ostream& os, const Farey_fraction& f); // �������� ������ ��� ������ �����
	// ========= ������ ������� � ����� ========= //
	BigInt get_numerator() const;
	BigInt get_denominator() const;
	BigInt get_num() const;
	BigInt get_mod() const;
	BigInt get_N() const;
	// ========= ����������� � long double ========= //
	long double to_long_double() const;
private:
	BigInt numerator{0};  // ��������� ����� �����
	BigInt denominator{1}; // ����������� ����� �����
	BigInt mod{_MOD}; // ������
	BigInt N{_N}; // ������� ����� �����
	BigInt num; // ����� � ���������� ����������, ��������������� ����� �����
	void calc(); // ����� num �� ����� �����
	void Normalize(); // �� ������ � ����� �� ������.
	void reverse_calc();   // ����� ����� �� num � ������� ������������ ��������� �������
	BigInt inverse_modulo(const BigInt&, const BigInt&); // ����� �������� ����� �� ������ � ������� ������������ ��������� �������
	Farey_fraction swapped(const Farey_fraction&); // ���������� ����� ����� (��� �������)
	void throw_if_bad_params(); // ������ ���������� ��� �������� ����� � ��������� �����������
	
};

bool is_prime(const BigInt& num);
int checkParams( BigInt& mod,  BigInt& N);  // ���������, ����������� �� �������� ������� ������ �����
bool valid_num(const std::string& s);	// ��������, �������� �� ������ ���������� � �������� ������������� ��������
BigInt operator "" _bg(const char* str, size_t sze); // ��������������� �������