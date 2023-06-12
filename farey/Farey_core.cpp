#include "Farey_core.h"
#include <exception>
#include <string>

bool no_overflow(int128_t  a, int128_t  b) {
    int128_t  sum = a + b;
    int128_t  ssd = a ^ b;
    if ((ssd >= 0) && ((ssd ^ sum) < 0)) {
        std::cout << "Overflow!!" << std::endl;
        return false;
    }
    return true;
}

int128_t  safe_mul(int128_t  x, int128_t  y, int128_t  m) {
    bool minus = x > 0 && y < 0 || x < 0 && y > 0;
    x = abs(x);
    y = abs(y);
    if (x > y) {
        int128_t  tmp = x;
        x = y;
        y = tmp;
    }
    int128_t  res = 0;
    int128_t  iy = y;
    while (x > 0) {
        if (x % 2 == 1) {
            if (!no_overflow(res, iy)) res -= m;
            res = (res + iy) % m;
        }
        int128_t  new_iy = iy;
        if (!no_overflow(new_iy, iy)) new_iy -= m;
        iy = (new_iy + iy) % m;
        //x >>= 1;
        x /= 2;
    }
    if (minus) res *= -1; 
    if (res != ((minus) ? (-1 * x * y) % m : (x * y) % m)) std::cout << "warning safe_mult" << "\n"; //!!!!!!
    return  res;
}

//int128_t abs(int128_t val) {
//    int128_t* res = &val;
//    if (val.cmp(0) == 1) return res->ap::library::integer_handle<256>::set_sign(0);
//    return val;
//}

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

std::string pow_10(int sze) {
    if (sze < 0) return "0." + std::string(abs(sze)-1, '0') + "1";
    return "1" + std::string(sze, '0');
}

bool valid_num(const std::string& s)  // минус прилегает плотно, в самом начале, не более чем одна точка
{ 
    //if (s.size() > 10) return false;
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
Farey_fraction::Farey_fraction(int128_t m, int128_t n, int128_t number) {
    mod = m;
    N = n;
    num = number;
    //std::cout << "number = " << number << " | N = " << N << std::endl;
    Normalize();
    reverse_calc();
}
Farey_fraction::Farey_fraction(int128_t m, int128_t n, int128_t num, int128_t denom) {
    mod = m;
    N = n;
    numerator = num;
    denominator = denom;
    Normalize();
    calc();
    
}

Farey_fraction::Farey_fraction(int128_t m, int128_t n, std::string number) : Farey_fraction(m,n,number,150,150) {}

Farey_fraction::Farey_fraction(int128_t m, int128_t n, std::string number, int prec, int significant) {
    if (!valid_num(number)) throw std::invalid_argument("Wrong floating point number representation"); // exception !
    // ПРОВЕРИТЬ: количество знаков после запятой не более 4, количество значащих цифр не больше 3
    // upd:  количество знаков после запятой не более 9, количество значащих цифр не больше 8
    mod = m;
    N = n;
    auto it = std::find(number.begin(), number.end(), '.'); // есть ли точка
    size_t dot_pos = std::distance(number.begin(), it);
    if (it == number.end()) {
        numerator = int128_t(number.data());
        denominator = 1;
        calc();
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
        if (count > prec) throw std::invalid_argument("Too much precision"); //!!!!!!!!
        bool minus = false;
        if (number[0] == '-') minus = true;
        int cnt1 = 0;                           // значащих цифр до точки
        bool found_non_zero = false;
        for (size_t i = (size_t)minus; i < dot_pos; i++) {
            if (!found_non_zero && number[i] == '0') continue;
            cnt1++;
            found_non_zero = true;
        } 
        int cnt2 = 0;
        for (size_t i = dot_pos + 1; i <= j; i++) {
            if (cnt1 == 0 && number[i] == '0') continue;  // пропускаем только если до точки не было значащих цифр
            cnt2++;
        }
        if (cnt1 + cnt2 > significant) throw std::invalid_argument("Too much significant digits");  //!!!!!!
        number = number.replace(j + 1 + int((j < dot_pos)), number.size() - j - 1 - int((j < dot_pos)), ""); // УДАЛИЛИ НЕЗНАЧАЩИЕ НУЛИ В КОНЦЕ
        //int denum_pow = number.size() - j;                                            // после запятой только нули, точку надо учесть и не удалять ее
        it = std::find(number.begin(), number.end(), '.');
        size_t dist = std::distance(number.begin(), it);
        int denom_pow = number.size() - dist - 1;
        number = number.replace(dist, 1, "");
        size_t first_not_null_pos = 0;
        for (first_not_null_pos = size_t(minus); first_not_null_pos < number.size(); first_not_null_pos++) {
            if (number[first_not_null_pos] >= '1' && number[first_not_null_pos] <= '9') {
                break;
            }
        }
        number = number.substr(first_not_null_pos, number.size() - first_not_null_pos);
        if (number == "") number = "0";
        numerator = int128_t(number.data());
        if (minus) numerator *= -1;
        denominator = int128_t(("1" + std::string(denom_pow, '0')).data());
        calc();
    }
}

Farey_fraction Farey_fraction::operator + (const Farey_fraction& rhs) {
    if (!no_overflow(num, rhs.get_num())) num -= mod; // проверка на переполнение
    Farey_fraction res(mod, N, (num + rhs.get_num()) % mod);
    return res;
}

Farey_fraction Farey_fraction::operator + (int64_t rhs) {
    return Farey_fraction::operator+(Farey_fraction(mod, N, rhs, 1));
}

Farey_fraction Farey_fraction::operator - (const Farey_fraction& rhs) {
    if (!no_overflow(num, -rhs.get_num())) num += mod; // проверка на переполнение ??? нужна ли
    Farey_fraction res(mod, N, (num + mod - rhs.get_num() ) % mod); //!!!!!
    return res;
}

Farey_fraction Farey_fraction::operator - (int64_t rhs) {
    return Farey_fraction::operator-(Farey_fraction(mod, N, rhs, 1));
}


Farey_fraction Farey_fraction::operator * (const Farey_fraction& rhs) {
    //Farey_fraction res(mod, N, safe_mul(num,rhs.get_num(), mod) % mod);
    Farey_fraction res(mod, N, (num * rhs.get_num()) % mod);
    return res;
}

Farey_fraction Farey_fraction::operator / (const Farey_fraction& rhs) {
    //Farey_fraction res(mod, N, safe_mul(num,swapped(rhs).get_num(),mod) % mod);
    Farey_fraction res(mod, N, (num * swapped(rhs).get_num()) % mod);
    return res;
}

Farey_fraction Farey_fraction::operator * (int64_t rhs) {
    return Farey_fraction::operator*(Farey_fraction(mod, N, rhs, 1));
}


Farey_fraction Farey_fraction::operator / (int64_t rhs) {
    return Farey_fraction::operator/(Farey_fraction(mod, N, rhs, 1));
}


Farey_fraction Farey_fraction::operator = (const Farey_fraction& rhs) {
    mod = rhs.get_mod();
    N = rhs.get_N();
    numerator = rhs.get_numerator();
    denominator = rhs.get_denominator();
    num = rhs.get_num();
    return *this;
}

Farey_fraction Farey_fraction::operator = (const std::string& rhs) {
    Farey_fraction res(mod, N, rhs);
    numerator = res.get_numerator();
    denominator = res.get_denominator();
    num = res.get_num();
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


int128_t Farey_fraction::get_numerator() const {
    return numerator;
}
int128_t Farey_fraction::get_denominator() const {
    return denominator;
}
int128_t Farey_fraction::get_num() const {
    return num;
}

int128_t Farey_fraction::get_mod() const {
    return mod;
}

int128_t Farey_fraction::get_N() const {
    return N;
}


long double Farey_fraction::to_long_double() const {
    return long double(numerator) / long double(denominator);
}
 
void Farey_fraction::Normalize() {
    while (num < 0) {
        num += mod;
    }
    num %= mod;
}

void Farey_fraction::calc() {
    int128_t inv = inverse_modulo(denominator, mod);
    while (inv < 0) {
        inv += mod;
    }
    inv %= mod;
    //num = safe_mul(numerator, inv, mod);
    num = numerator * inv % mod;
    Normalize();
}

int128_t Farey_fraction::inverse_modulo(int128_t num, int128_t mod) {
    int128_t M[2][2];
    M[0][0] = mod;
    M[1][0] = num;
    M[0][1] = 0;
    M[1][1] = 1;
    int128_t r = 0, q = 0;
    while (M[1][0] != 1) {
        r = M[0][0] % M[1][0];
        q = M[0][1] - M[0][0] / M[1][0] * M[1][1];
        M[0][0] = M[1][0];
        M[0][1] = M[1][1];
        M[1][0] = r;
        M[1][1] = q;
    }
    return M[1][1];
}

void Farey_fraction::reverse_calc() {
    int128_t M[2][2];
    M[0][0] = mod;
    M[0][1] = 0;
    M[1][0] = num;
    M[1][1] = 1;
    int128_t r = 0, q = 0;
    int64_t count = 0;
    while (abs(M[1][0] > N) || abs(M[1][1] > N)) { // 
    //while ((M[1][0] + mod) % mod > N || (M[1][1] + mod) % mod > N) { //
        r = M[0][0] % M[1][0];
        q = M[0][1] - (M[0][0] / M[1][0]) * M[1][1];
        M[0][0] = M[1][0];
        M[0][1] = M[1][1];
        M[1][0] = r;
        M[1][1] = q;
        if (M[1][0] == 0 && abs(M[1][1]) > N) {
            M[1][0] = mod;
        }
        count++;
        if (count > 10000) {
            std::cout << "Reverse_calc loop error. Parameters: num = " << num << ", mod = " << mod << std::endl;
            return;
        }
    }
    //numerator = (M[1][0] * (M[1][1] / abs(M[1][1])));
    numerator = (M[1][1] >= 0) ? M[1][0] : -M[1][0];
    denominator = (abs(M[1][1])); // static cast?
    if (numerator == 0) {
        denominator = 1;
    }
    
    {
        auto d = Farey_fraction(_MOD, _N, numerator, denominator);
        if (d.get_num() != num) std::cout << "AAAAAAAAAAAAAAAAA\n";
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
    os << f.get_numerator() << '/' << f.get_denominator();
    return os;
}

