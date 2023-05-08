//#include <iostream>
#include "Farey_core.h"

using namespace std;


int main()
{
    //BigInt mod = 9223372036854775783; // (uint64_t??) максимальное простое число, представимое в BigInt (в обратном расчете используется именно BigInt)
   // BigInt n = 2147483647;  // up to 2147483647
    BigInt mod = "9999999999999999999999999999999999999983"s; // зарандомил)))()())(
    BigInt n = "70710678118654752440"s;
    cout << "Mod: " << mod << endl;
   // cin >> mod;
    cout << "N: " << n << endl;
   // cin >> n;
    BigInt num, denom;
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
