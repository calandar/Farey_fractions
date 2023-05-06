//#include <iostream>
#include "Farey_core.h"

using namespace std;

int main()
{
    int64_t mod = 9223372036854775783; // (uint64_t??) максимальное простое число, представимое в int64_t (в обратном расчете используется именно int64_t)
    int64_t n = 2147483647;  // up to 2147483647

    cout << "Mod: " << mod << endl;
   // cin >> mod;
    cout << "N: " << n << endl;
   // cin >> n;
    int64_t num, denom;
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
