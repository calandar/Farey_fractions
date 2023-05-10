//#include <iostream>
#include "Farey_core.h"
#include "scalar.h"

using namespace std;


int main()
{
    setlocale(LC_ALL, ".1251");
    //BigInt mod = 9223372036854775783; // (uint64_t??) максимальное простое число, представимое в BigInt (в обратном расчете используется именно BigInt)
   // BigInt n = 2147483647;  // up to 2147483647
    BigInt mod = "9999999999999999999999999999999999999983"s; // зарандомил)))()())(
    BigInt n = "70710678118654752440"s;
    cout << "Mod: " << mod << endl;
   // cin >> mod;
    cout << "N: " << n << endl;
   // cin >> n;
    BigInt num, denom;
    cout << "1 - Тест конструктора через дроби. 2 - Тест конструктора через числа. 3 - Тест скалярного произведения\n";
    char com;
    cin >> com;
    if (com == '1') {
        while (1) {
            // 123/456+567/789
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
                Farey_fraction res = a + b;
                cout << res << endl;
                cout << res.get_numerator().to_long_long() / double(res.get_denominator().to_long_long());
            }

            else if (op == '-') {
                Farey_fraction res = a + b;
                cout << res << endl;
            }

            else if (op == '*') {
                Farey_fraction res = a + b;
                cout << res << endl;
            }
            else if (op == '/') {
                Farey_fraction res = a + b;
                cout << res << endl;
            }

        }
    }
    else if (com == '2'){
        while (1) {
            BigInt num1;
            cin >> num1;
            Farey_fraction a(mod, n, num1);
            char op;
            cin >> op;
            BigInt num2;
            cin >> num2;
            Farey_fraction b(mod, n, num2);
            Farey_fraction res = a + b;
            cout << res << endl;
        }
    }
    else {
        while (1) {
/*1.25
0.356
1.339
-0.345
12.35
-2.35*/
            size_t n;
            cout << "Dimentions of 2 vectors: " << endl;
            cin >> n;
            string curr;
            vector<string> v1(n);
            for (size_t i = 0; i < n; i++) {
                cin >> curr;
                if (valid_num(curr)) v1[i] = curr;
                else {
                    cout << "Error number representation\n";
                    exit(1337);
                }
            }
            vector<string> v2(n);
            
            for (size_t i = 0; i < n; i++) {
                cin >> curr;
                if (valid_num(curr)) v2[i] = curr;
                else {
                    cout << "Error number representation\n";
                    exit(1337);
                }
            }
            vec vec1(v1);
            vec vec2(v2);
            cout << scalar(vec1, vec2) << endl;
            vec1.print_vec();
            vec2.print_vec();
        }
    }
}
