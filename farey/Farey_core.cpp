#include "Farey_core.h"
#include <exception>

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

Farey_fraction::Farey_fraction(){
    calc();
}
Farey_fraction::Farey_fraction(const BigInt& m, const BigInt& n, const BigInt& number) {
    mod = m;
    N = n;
    throw_if_bad_params();
    num = number;
    Normalize();
    reverse_calc();
}
Farey_fraction::Farey_fraction(const BigInt& m, const BigInt& n, const BigInt& num, const BigInt& denom) {
    mod = m;
    N = n;
    throw_if_bad_params();
    numerator = num;
    denominator = denom;
    Normalize();
    calc();
    
}

Farey_fraction::Farey_fraction(const BigInt& m, const BigInt& n, std::string number, bool simplify) {
    if (!valid_num(number)) throw std::invalid_argument("Wrong floating point number representation"); // exception !
    mod = m;
    N = n;
    throw_if_bad_params();
    strip_leading_zeroes(number); // from bigint.h
    int i = number.size() - 1;
    while (i >= 0 && number[i] == '0') {
        --i;
    }
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
        BigInt numer = number.replace(dist, 1, "");
        BigInt denomin = big_pow10(number.size() - dist);
        
        if (!simplify) {
            numerator = numer;
            denominator = denomin;
        }
        else {
            BigInt g = gcd(numer, denomin);
            numerator = numer / g;
            denominator = denomin / g;
        }
        calc();
    }
}

Farey_fraction Farey_fraction::operator + (const Farey_fraction& rhs) {
    Farey_fraction res(mod, N, (num + rhs.get_num()) % mod);
    return res;
}
Farey_fraction Farey_fraction::operator - (const Farey_fraction& rhs) {
    Farey_fraction res(mod, N, (num - rhs.get_num()) % mod);
    return res;
}

Farey_fraction Farey_fraction::operator * (const Farey_fraction& rhs) {
    Farey_fraction res(mod, N, (num * rhs.get_num()) % mod);
    return res;
}

Farey_fraction Farey_fraction::operator / (const Farey_fraction& rhs) {
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


Farey_fraction& Farey_fraction::operator -= (const Farey_fraction& rhs) {
    *this = *this - rhs;
    return *this;
}

Farey_fraction& Farey_fraction::operator *= (const Farey_fraction& rhs) {
    *this = *this * rhs;
    return *this;
}

Farey_fraction& Farey_fraction::operator /= (const Farey_fraction& rhs) {
    *this = *this / rhs;
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
        std::cout << "Failed conversion into long double" << std::endl;
        std::cout << "Corresponding Farey fraction: " << *this << std::endl;
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
    num = (numerator * inv) % mod;
}

BigInt Farey_fraction::inverse_modulo(const BigInt& num,const BigInt& mod) {
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

void Farey_fraction::throw_if_bad_params() {
    if (checkParams(mod, N) != 1) {
        std::cout << "Invalid parameters of Farey fractions" << std::endl;
        throw std::invalid_argument("Invalid parameters of Farey fractions");
    }
}

bool is_prime(const BigInt& num) {
    if (num == 1) return false;
    if (num == 2) return true;
    if (num % 2 == 0) return false;
    BigInt upper = sqrt(num);
    for (BigInt i = 3; i <= upper; i+=2) {
        if (num % i == 0) return false;
    }
    return true;
}

int checkParams( BigInt& mod,  BigInt& N) {
    return N * N * 2ll + 1ll <= mod && mod > 1 && N > 1 /*&& is_prime(mod)*/;
}

Farey_fraction Farey_fraction::swapped(const Farey_fraction& f) {
    return Farey_fraction(mod, N, f.get_denominator(), f.get_numerator());
}


std::ostream& operator << (std::ostream& os, const Farey_fraction& f) {
    os << f.get_numerator() << '/' << f.get_denominator() << std::endl;
    return os;
}

