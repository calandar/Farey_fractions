#pragma once
#include <cstdint>
#include <iostream>

int64_t inverse_modulo(int64_t num, int64_t mod); // ���������� ����� ������� ����� ��� ���������� ��������� �����
int64_t bin_pow(int64_t a, uint64_t n, uint64_t mod); // �������� ���������� � �������


class Farey_fraction {
public:
	Farey_fraction();
	Farey_fraction(int64_t m, int64_t n, int64_t number);
	Farey_fraction(int64_t m, int64_t n, int64_t num, int64_t denom);
	Farey_fraction& operator + (const Farey_fraction& rhs);
	Farey_fraction& operator - (const Farey_fraction& rhs);
	Farey_fraction& operator * (const Farey_fraction& rhs);
	Farey_fraction& operator / (const Farey_fraction& rhs);
	int64_t get_numerator() const;
	int64_t get_denominator() const;
	int64_t get_num() const;
private:
	int64_t numerator;  // ��������� ����� �����
	int64_t denominator; // ����������� ����� �����
	int64_t mod; // ������
	int64_t N; // ������� ����� �����
	int64_t num; // ����� � ���������� ����������, ��������������� ����� �����
	void calc();
	void Normalize();
	void reverse_calc();   // ����� ����� �� num � ������� ������������ ��������� �������
	Farey_fraction swapped(const Farey_fraction& f);
	
};

std::ostream& operator << (std::ostream& os, const Farey_fraction& f);