#include "Farey_core.h"
#include <exception>
#include <string>

bool no_overflow(int64_t a, int64_t b) {  
    int64_t sum = a + b;
    int64_t ssd = a ^ b;
    if ((ssd >= 0) && ((ssd ^ sum) < 0))
        return false; 
    return true;
}

int64_t safe_mul(int64_t x, int64_t y, int64_t m) { 
    if (x > y) {
        int64_t tmp = x;
        x = y;
        y = tmp;
    }
    int64_t res = 0;
    int64_t iy = y;
    while (x) {
        if (x & 1) {
            if (!no_overflow(res, iy)) res -= m;
            res = (res + iy) % m;
        }
        int64_t new_iy = iy;
        if (!no_overflow(new_iy, iy)) new_iy -= m;
        iy = (new_iy + iy) % m;
        x >>= 1;
    }
    return  res;
}


void strip_leading_zeroes(std::string& num) {
    size_t i;
    for (i = 0; i < num.size(); i++)
        if (num[i] != '0')
            break;

    if (i == num.size())
        num = "0";
    else
        num = num.substr(i);
}

bool valid_num(const std::string& s)  // минус прилегает плотно, в самом начале, не более чем одна точка
{ 
    if (s.size() > 8) return false;
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
    return (!s.empty() && it == s.end()); // формат строки норм -> далее проверка
  
}

Farey_fraction::Farey_fraction(){
    calc();
}
Farey_fraction::Farey_fraction(int64_t m, int64_t n, int64_t number) {
    mod = m;
    N = n;
    //throw_if_bad_params();  // ??
    num = number;
    Normalize();
    reverse_calc();
}
Farey_fraction::Farey_fraction(int64_t m, int64_t n, int64_t num, int64_t denom) {
    mod = m;
    N = n;
    //throw_if_bad_params(); // ?
    numerator = num;
    denominator = denom;
    Normalize();
    calc();
    
}

Farey_fraction::Farey_fraction(int64_t m, int64_t n, std::string number) {
    if (!valid_num(number)) throw std::invalid_argument("Wrong floating point number representation"); // exception !
    // ПРОВЕРИТЬ: количество знаков после запятой не более 4, количество значащих цифр не больше 3
    mod = m;
    N = n;
    auto it = std::find(number.begin(), number.end(), '.'); // есть ли точка
    size_t dot_pos = std::distance(number.begin(), it);
    if (it == number.end()) {
        numerator = std::stoll(number);
        denominator = 1;
    }
    else {
        // точка есть
        size_t j = number.size() - 1; // Удаляем незначащие нули в конце, в j - позиция последнего НЕ нуля
        while (j > dot_pos) {
            if (number[j] != '0') break;
            j--;
        }
        if (number[j] == '.') j--;
        // 42.0  -> [j] = '.'
        int count = 0; // ищем сколько цифр после точки
        for (size_t i = dot_pos + 1; i <= j; i++) {
            count++;
        }
        if (count > 4) throw std::invalid_argument("Too much precision");
        bool minus = false;
        if (number[0] == '-') minus = true;
        int cnt1 = 0;
        for (size_t i = (size_t)minus; i < dot_pos; i++) {
            if (number[i] == '0') continue;
            cnt1++;
        } 
        int cnt2 = j - cnt1;
        if (cnt1 + cnt2 > 3) throw std::invalid_argument("Too much significant digits");
        size_t first_not_null_pos = 0;
        for (first_not_null_pos = size_t(minus); first_not_null_pos < number.size(); first_not_null_pos++) {
            if (number[first_not_null_pos] >= '1' && number[first_not_null_pos] <= '9') {
                break;
            }
            first_not_null_pos++;
        }
        number = number.replace(j + 1 + int((j < dot_pos)), number.size() - j - 1 - int((j < dot_pos)), ""); // УДАЛИЛИ НЕЗНАЧАЩИЕ НУЛИ В КОНЦЕ
        //int denum_pow = number.size() - j;                                            // после запятой только нули, точку надо учесть и не удалять ее
        it = std::find(number.begin(), number.end(), '.');
        size_t dist = std::distance(number.begin(), it);
        int denom_pow = number.size() - dist - 1;
        number = number.replace(dist, 1, "");
        number = number.substr(first_not_null_pos, number.size() - first_not_null_pos);
        numerator = stoll(number);
        if (minus) numerator *= -1;
        denominator = stoll("1" + std::string(denom_pow, '0'));
        calc();
    }
}

Farey_fraction Farey_fraction::operator + (const Farey_fraction& rhs) {
    if (!no_overflow(num, rhs.get_num())) num -= mod; // проверка на переполнение
    Farey_fraction res(mod, N, (num + rhs.get_num()) % mod);
    return res;
}
Farey_fraction Farey_fraction::operator - (const Farey_fraction& rhs) {
    //if (!no_overflow(num, -rhs.get_num())) num -= mod; // проверка на переполнение ??? нужна ли
    Farey_fraction res(mod, N, (num - rhs.get_num()) % mod);
    return res;
}

Farey_fraction Farey_fraction::operator * (const Farey_fraction& rhs) {
    Farey_fraction res(mod, N, safe_mul(num,rhs.get_num(), mod) % mod);
    return res;
}

Farey_fraction Farey_fraction::operator / (const Farey_fraction& rhs) {
    Farey_fraction res(mod, N, safe_mul(num,swapped(rhs).get_num(),mod) % mod);
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


int64_t Farey_fraction::get_numerator() const {
    return numerator;
}
int64_t Farey_fraction::get_denominator() const {
    return denominator;
}
int64_t Farey_fraction::get_num() const {
    return num;
}

int64_t Farey_fraction::get_mod() const {
    return mod;
}

int64_t Farey_fraction::get_N() const {
    return N;
}


long double Farey_fraction::to_long_double() const {
    return numerator / long double(denominator);
}
 
void Farey_fraction::Normalize() {
    while (num < 0) {
        num += mod;
    }
    num %= mod;
}

void Farey_fraction::calc() {
    int64_t inv = inverse_modulo(denominator, mod);
    while (inv < 0) {
        inv += mod;
    }
    inv %= mod;
    num = safe_mul(numerator, inv, mod);
}

int64_t Farey_fraction::inverse_modulo(int64_t num, int64_t mod) {
    int64_t M[2][2];
    M[0][0] = mod;
    M[1][0] = num;
    M[0][1] = 0;
    M[1][1] = 1;
    int64_t r = 0, q = 0;
    while (M[1][0] != 1) {
        r = M[0][0] % M[1][0];
        q = M[0][1] - M[0][0] / M[1][0] * M[1][1];
        M[0][0] = M[1][0];
        M[0][1] = M[1][1];
        M[1][0] = r;
        M[1][1] = q;
    }
    return M[1][1];
    // Normalize()????
}

void Farey_fraction::reverse_calc() {
    int64_t M[2][2];
    M[0][0] = mod;
    M[0][1] = 0;
    M[1][0] = num;
    M[1][1] = 1;
    int64_t r = 0, q = 0;

    while (abs(M[1][0] > N) || abs(M[1][1] > N)) { // 
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
    numerator = (M[1][0] * (M[1][1] / abs(M[1][1])));
    denominator = (abs(M[1][1])); // static cast?
    if (numerator == 0) {
        denominator = 1;
    }
}


//bool is_prime(const BigInt& num) {
//    if (num == 1) return false;
//    if (num == 2) return true;
//    if (num % 2 == 0) return false;
//    BigInt upper = sqrt(num);
//    for (BigInt i = 3; i <= upper; i+=2) {
//        if (num % i == 0) return false;
//    }
//    return true;
//}
//
//int checkParams( BigInt& mod,  BigInt& N) {
//    return N * N * 2ll + 1ll <= mod && mod > 1 && N > 1 /*&& is_prime(mod)*/;
//}

Farey_fraction Farey_fraction::swapped(const Farey_fraction& f) {
    return Farey_fraction(mod, N, f.get_denominator(), f.get_numerator());
}


std::ostream& operator << (std::ostream& os, const Farey_fraction& f) {
    os << f.get_numerator() << '/' << f.get_denominator() << std::endl;
    return os;
}

