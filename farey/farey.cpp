
#include <iostream>


using namespace std;


int64_t inverse_modulo(int64_t num, int64_t mod);

class Farey_fraction {
public:

    Farey_fraction() {}
    Farey_fraction(int64_t m, unsigned int n, int64_t number) {
        mod = m;
        N = n;
        num = number;
        //calc();
    }

    Farey_fraction(int64_t m, unsigned int n, int64_t num, int64_t denom) {
        mod = m;
        N = n;
        numerator = num;
        denominator = denom;
        calc();
    }

    Farey_fraction& operator + (const Farey_fraction& rhs) {
        this->num = (num + rhs.get_num()) % mod;
        Normalize();
        reverse_calc();
        return *this;
    }

    Farey_fraction& operator - (const Farey_fraction& rhs) {
        this->num = (num - rhs.get_num()) % mod;
        Normalize();
        reverse_calc();
        return *this;
    }

    Farey_fraction& operator * (const Farey_fraction& rhs) {
        this->num = (num * rhs.get_num()) % mod;
        Normalize();
        reverse_calc();
        return *this;
    }

    Farey_fraction& operator / (const Farey_fraction& rhs) {
        this->num = (num * swapped(rhs).get_num()) % mod;
        Normalize();
        reverse_calc();
        return *this;
    }

    int64_t get_numerator() const {
        return numerator;
    }

    int64_t get_denominator() const {
        return denominator;
    }

    int64_t get_num() const {
        return num;
    }




private:
    int64_t numerator = 0;  // Числитель дроби Фарея
    int64_t denominator = 1; // Знаменитель дроби Фарея
    int64_t mod = 19; // Модуль
    unsigned int N = 3; // Порядок дроби Фарея
    int64_t num = 0; // Число в модулярной арифметике, соответствующее дроби Фарея

    void calc() {
        num = numerator * inverse_modulo(denominator, mod) % mod;  // найти num по значению дроби
    }

    void reverse_calc() {   // найти дробь по num с помощью расширенного алгоритма Евклида
        int64_t M[2][2];
        M[0][0] = mod;
        M[0][1] = 0;
        M[1][0] = num;
        M[1][1] = 1;
        int64_t r = 0, q = 0;

        while (abs(M[1][0] > (int)N) || abs(M[1][1] > (int)N)) { // 
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
        numerator = static_cast<int64_t>(M[1][0] * (M[1][1] / abs(M[1][1])));
        denominator = static_cast<int64_t>(abs(M[1][1]));
        if (numerator == 0) {
            denominator = 1;
        }
    }

    void Normalize() {
        while (num < 0) {
            num += mod;
        }
        num %= mod;

    }

    Farey_fraction swapped(const Farey_fraction& f) {
        return Farey_fraction(mod, N, f.get_denominator(), f.get_numerator());
    }

};


int64_t bin_pow(int64_t a, uint64_t n, uint64_t mod) { // бинарное возведение в степень
    int64_t res = 1;
    while (n) {
        if (n % 2 == 1) res = res * a % mod;
        a = a * a % mod;
        n >>= 1; // n = n / 2;
    }
    return res;
}



int64_t inverse_modulo(int64_t num, int64_t mod) { // используем малую теорему Ферма для нахождения обратного числа
    return bin_pow(num, mod - 2, mod); // !!!! int?
}


ostream& operator << (ostream& os, const Farey_fraction& f) {
    os << f.get_numerator() << '/' << f.get_denominator();
    return os;
}



int main()
{

    uint64_t mod = 20011;
    unsigned n;  // up to 100

    cout << "Mod: " << mod << endl;
   // cin >> mod;
    cout << "N: ";
    cin >> n;
    int num, denom;
    while (1) {

        cin >> num;
        cin.ignore();
        cin >> denom;
        Farey_fraction a(mod, n, num, denom);

        char op;

        cin >> op;

        cin >> num;
        cin.ignore();
        cin >> denom;
        Farey_fraction b(mod, n, num, denom);

        if (op == '+') {
            cout << a + b << endl;
        }

        else if (op == '-') {
            cout << a - b << endl;
        }

        else if (op == '*') {
            cout << a * b << endl;
        }
        else if (op == '/') {
            cout << a / b << endl;
        }


    }

}
