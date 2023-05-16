#pragma once
#include <iostream>


// ========= �������� ���������� �� ��������� ========= //
#define _MOD 9223372036854775783
#define _N 2147483647
#define _MOD2 BigInt("999999999999999999999999999999999999999999999999999999999839")
#define _N2 BigInt("707106781186547524400844362104") // ��� 30 ��������

class Farey_fraction {
public:
	// ========= ������������ ========= //
	Farey_fraction();
	Farey_fraction(int64_t, int64_t, int64_t); 
	Farey_fraction(int64_t, int64_t, int64_t, int64_t);
	Farey_fraction(int64_t, int64_t, std::string);	// REWORKING
	// ========= ������������� �������������� ��������� ========= //
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
	// ========= ��������� �����/������ ========= //
	//friend std::istream& operator >> (std::istream& is, Farey_fraction& f);  // �������� ����� ��� ������ ����� (impossible?)
    friend std::ostream& operator << (std::ostream& os, const Farey_fraction& f); // �������� ������ ��� ������ �����
	// ========= ������ ������� � ����� ========= //
	int64_t get_numerator() const;
	int64_t get_denominator() const;
	int64_t get_num() const;
	int64_t get_mod() const;
	int64_t get_N() const;
	// ========= ����������� � long double ========= //
	long double to_long_double() const;
private:
	int64_t numerator{0};  // ��������� ����� �����
	int64_t denominator{1}; // ����������� ����� �����
	int64_t mod{_MOD}; // ������
	int64_t N{_N}; // ������� ����� �����
	int64_t num; // ����� � ���������� ����������, ��������������� ����� �����
	void calc(); // ����� num �� ����� �����
	void Normalize(); // �� ������ � ����� �� ������.
	void reverse_calc();   // ����� ����� �� num � ������� ������������ ��������� �������
	int64_t inverse_modulo(int64_t, int64_t); // ����� �������� ����� �� ������ � ������� ������������ ��������� �������
	Farey_fraction swapped(const Farey_fraction&); // ���������� ����� ����� (��� �������)
	
};

//bool is_prime(const BigInt& num);
//int checkParams( BigInt& mod,  BigInt& N);  // ���������, ����������� �� �������� ������� ������ �����
bool valid_num(const std::string& s);	// ��������, �������� �� ������ ���������� � �������� ������������� ��������
bool no_overflow(int64_t, int64_t);
int64_t safe_mul(int64_t, int64_t, int64_t);
void strip_leading_zeroes(std::string&);