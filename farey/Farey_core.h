#pragma once
//#include <cstdint>
#include <iostream>
#include "BigInt.h"

//BigInt inverse_modulo(BigInt num, BigInt mod); // ���������� ����� ������� ����� ��� ���������� ��������� �����
//BigInt bin_pow(BigInt a, uint64_t n, uint64_t mod); // �������� ���������� � �������



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
	BigInt numerator;  // ��������� ����� �����
	BigInt denominator; // ����������� ����� �����
	BigInt mod; // ������
	BigInt N; // ������� ����� �����
	BigInt num; // ����� � ���������� ����������, ��������������� ����� �����
	void calc();
	void Normalize();
	void reverse_calc();   // ����� ����� �� num � ������� ������������ ��������� �������
	Farey_fraction swapped(const Farey_fraction& f);
	
};

std::ostream& operator << (std::ostream& os, const Farey_fraction& f);