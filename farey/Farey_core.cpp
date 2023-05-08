#include "Farey_core.h"


/* TODO:
        1. Проверка на деление на 0
*/



//bool no_overflow(BigInt a, BigInt b) {  // header??!
//    BigInt sum = a + b;
//    BigInt ssd = a ^ b;
//    if ((ssd >= 0) && ((ssd ^ sum) < 0))
//        return false; // если переполнение - false
//    return true;
//}

//BigInt safe_mul(BigInt x, BigInt y, BigInt m) { // в header?!
//    if (x > y) {
//        BigInt tmp = x;
//        x = y;
//        y = tmp;
//    }
//    BigInt res = 0;
//    BigInt iy = y;
//    while (x) {
//        if (x & 1) {
//            if (!no_overflow(res, iy)) res -= m;
//            res = (res + iy) % m;
//        }
//        BigInt new_iy = iy;
//        if (!no_overflow(new_iy, iy)) new_iy -= m;
//        iy = (new_iy + iy) % m;
//        x >>= 1;
//    }
//    return  res;
//}


//BigInt bin_pow(BigInt a, BigInt n, BigInt mod) { // бинарное возведение в степень
//    BigInt res = 1;
//    while (n) {
//        if (n % 2 == 1) res = ((res % mod) * a) % mod;
//        a = a * a % mod;
//        n >>= 1; // n = n / 2;
//    }
//    return res;
//}

//BigInt inverse_modulo(BigInt num, BigInt mod) { // используем малую теорему Ферма для нахождения обратного числа
//    return bin_pow(num, mod - 2, mod); // !!!! int?
//}

BigInt inverse_modulo(BigInt num, BigInt mod) {
    BigInt M[2][2];
    M[0][0] = mod;
    M[1][0] = num;
    M[0][1] = 0;
    M[1][1] = 1;
    BigInt r = 0, q = 0;
    while (M[1][0] != 1) {
        r = M[0][0] % M[1][0];
        q = M[0][1] - M[0][0] / M[1][0] * M[1][1];
        M[0][0] = M[1][0];
        M[0][1] = M[1][1];
        M[1][0] = r;
        M[1][1] = q;
    }
    auto res = M[1][1];
    return res;
    // Normalize()????
}

Farey_fraction::Farey_fraction() {}
Farey_fraction::Farey_fraction(BigInt m, BigInt n, BigInt number) {
    mod = m;
    N = n;
    num = number;
}
Farey_fraction::Farey_fraction(BigInt m, BigInt n, BigInt num, BigInt denom) {
    mod = m;
    N = n;
    numerator = num;
    denominator = denom;
    calc();
    Normalize();
}
/*
// обычные операторы дадут переполнение, пробуем сейвово считать
//Farey_fraction& Farey_fraction::operator + (const Farey_fraction& rhs) {
//    this->num = (num + rhs.get_num()) % mod;
//    Normalize();
//    reverse_calc();
//    return *this;
//}
//Farey_fraction& Farey_fraction::operator - (const Farey_fraction& rhs) {
//    this->num = (num - rhs.get_num()) % mod;
//    Normalize();
//    reverse_calc();
//    return *this;
//}
//
//Farey_fraction& Farey_fraction::operator * (const Farey_fraction& rhs) {
//    this->num = (num * rhs.get_num()) % mod;
//    Normalize();
//    reverse_calc();
//    return *this;
//}
//Farey_fraction& Farey_fraction::operator / (const Farey_fraction& rhs) {
//    this->num = (num * swapped(rhs).get_num()) % mod;
//    Normalize();
//    reverse_calc();
//    return *this;
//}*/  //старые операторы

Farey_fraction& Farey_fraction::operator + (const Farey_fraction& rhs) {
   // if (!no_overflow(num, rhs.get_num())) num -= mod; // аккуратно с переполнением
    this->num = (num + rhs.get_num()) % mod;
    Normalize();
    reverse_calc();
    return *this;
}
Farey_fraction& Farey_fraction::operator - (const Farey_fraction& rhs) {
    //if (!no_overflow(num, -rhs.get_num())) num -= mod; // тут по идее не надо обрабатывать переполнения
    this->num = (num - rhs.get_num()) % mod;
    Normalize();
    reverse_calc();
    return *this;
}

Farey_fraction& Farey_fraction::operator * (const Farey_fraction& rhs) {
  //  this->num = safe_mul(num, rhs.get_num(), mod);
    this->num = (num * rhs.get_num()) % mod;
    Normalize();
    reverse_calc();
    return *this;
}
Farey_fraction& Farey_fraction::operator / (const Farey_fraction& rhs) {
    //this->num = safe_mul(num, swapped(rhs).get_num(), mod);
    this->num = (num * swapped(rhs).get_num()) % mod;
    Normalize();
    reverse_calc();
    return *this;
}

BigInt Farey_fraction::get_numerator() const {
    return numerator;
}
BigInt Farey_fraction::get_denominator() const {
    return denominator;
}
BigInt Farey_fraction::get_num() const {
    return num;
}

void Farey_fraction::Normalize() {
    while (num < 0) {
        num += mod;
    }
    num %= mod;
}

void Farey_fraction::calc() {
    auto inv = inverse_modulo(denominator, mod);
    while (inv < 0) {
        inv += mod;
    }
    inv %= mod;
    //num = (numerator * inv) % mod;  // ОПАСНО: ПЕРЕПОЛНЕНИЕ :cccccccccccccccccccccccccccc
   // num = safe_mul(numerator, inv, mod);
    num = (numerator * inv) % mod;
}

void Farey_fraction::reverse_calc() {
    BigInt M[2][2];
    M[0][0] = static_cast<BigInt>(mod);
    M[0][1] = 0;
    M[1][0] = num;
    M[1][1] = 1;
    BigInt r = 0, q = 0;

    while (abs(M[1][0] > (BigInt)N) || abs(M[1][1] > (BigInt)N)) { // 
        r = M[0][0] % M[1][0];
        q = M[0][1] - (M[0][0] / M[1][0]) * M[1][1];
        M[0][0] = M[1][0];
        M[0][1] = M[1][1];
        M[1][0] = r;
        M[1][1] = q;
        if (M[1][0] == 0 && abs(M[1][1]) > N) {
            M[1][0] = mod;
        }
    }
    numerator = static_cast<BigInt>(M[1][0] * (M[1][1] / abs(M[1][1])));
    denominator = static_cast<BigInt>(abs(M[1][1]));
    if (numerator == 0) {
        denominator = 1;
    }
}

Farey_fraction Farey_fraction::swapped(const Farey_fraction& f) {
    return Farey_fraction(mod, N, f.get_denominator(), f.get_numerator());
}

std::ostream& operator << (std::ostream& os, const Farey_fraction& f) {
    os << f.get_numerator() << '/' << f.get_denominator();
    return os;
}