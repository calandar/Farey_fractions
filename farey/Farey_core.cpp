#include "Farey_core.h"
#include <exception>

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


BigInt operator "" _bg(const char* str, size_t sze) {
    return BigInt(str);
}

bool valid_num(const std::string& s)  // минус прилегает плотно, в самом начале, одна точка
{
    bool found_dot = false;
    std::string::const_iterator it = s.begin();
    while (it != s.end()) {
    if (*it == '.') {
        if (found_dot || std::distance(s.begin(),it) == s.size()-1) return false;
        found_dot = true;
    }
    else if (*it == '-') {
        if (it != s.begin()) return false; // если минус не в начале
    }
    else if (!(std::isdigit(*it))) return false;
    ++it;
    }
return !s.empty() && it == s.end();
}

Farey_fraction::Farey_fraction() {}
Farey_fraction::Farey_fraction(BigInt m, BigInt n, BigInt number) {
    mod = m;
    N = n;
    num = number;
    reverse_calc();
    Normalize();
}
Farey_fraction::Farey_fraction(BigInt m, BigInt n, BigInt num, BigInt denom) {
    mod = m;
    N = n;
    numerator = num;
    denominator = denom;
    calc();
    Normalize();
}

Farey_fraction::Farey_fraction(BigInt m, BigInt n, std::string number) {  // протестировать!"!!1!!!1!!1!11
    mod = m;
    N = n;
    strip_leading_zeroes(number); // from bigint.h
    int i = number.size() - 1;
    while (i >= 0 && number[i] == '0') {
        --i;
    }
    //if (number[i] == '.') ++i;
    if (i != number.size()-1) number = number.substr(0, i + 1); // удалили нули спереди и сзади
    auto it = std::find(number.begin(), number.end(), '.');
    if (it == number.end()) {
        numerator = number;
        denominator = "1";
    }
    else {
        size_t j = 0;
        bool minus = false;
        bool found = false;
        if (number[j] == '-') {
            j++;
            minus = true;
        }
        while (j < number.size() && number[j] == '0') {
            j++;
            found = true;
        }
        number = number.replace(int(minus), int(found)* (j - int(minus)), "");
        it = std::find(number.begin(), number.end(), '.');
        size_t dist = std::distance(number.begin(), it);
        numerator = number.replace(dist, 1, "");
        denominator = big_pow10(number.size() - dist);
        calc();
    }
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

Farey_fraction Farey_fraction::operator + (const Farey_fraction& rhs) {
   // if (!no_overflow(num, rhs.get_num())) num -= mod; // аккуратно с переполнением

    Farey_fraction res(mod, N, (num + rhs.get_num()) % mod);
    return res;
}
Farey_fraction Farey_fraction::operator - (const Farey_fraction& rhs) {
    //if (!no_overflow(num, -rhs.get_num())) num -= mod; // тут по идее не надо обрабатывать переполнения

    Farey_fraction res(mod, N, (num - rhs.get_num()) % mod);
    return res;
}

Farey_fraction Farey_fraction::operator * (const Farey_fraction& rhs) {
  //  this->num = safe_mul(num, rhs.get_num(), mod);
    Farey_fraction res(mod, N, (num * rhs.get_num()) % mod);
    return res;
}

Farey_fraction Farey_fraction::operator / (const Farey_fraction& rhs) {
    //this->num = safe_mul(num, swapped(rhs).get_num(), mod);
    Farey_fraction res(mod, N, (num * swapped(rhs).get_num()) % mod);
    return res;
}

Farey_fraction& Farey_fraction::operator = (const Farey_fraction& rhs) {
    mod = rhs.get_mod();
    N = rhs.get_N();
    numerator = rhs.get_numerator();
    denominator = rhs.get_denominator();
    num = rhs.get_num();
    return *this;
}

Farey_fraction& Farey_fraction::operator += (const Farey_fraction& rhs) {
    *this = *this + rhs;
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

BigInt Farey_fraction::get_mod() const {
    return mod;
}

BigInt Farey_fraction::get_N() const {
    return N;
}

long double Farey_fraction::to_long_double() const {
    try {
        int64_t denom = denominator.to_long_long();
        int64_t integral_part = (numerator / denominator).to_long_long();
        long double res = (numerator % denominator).to_long_long() / long double(denom);
        return res + integral_part;
    }
    catch (std::exception& e) {
        std::cout << e.what() << std::endl;
        return 0;
    }
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

BigInt Farey_fraction::inverse_modulo(BigInt num, BigInt mod) {
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