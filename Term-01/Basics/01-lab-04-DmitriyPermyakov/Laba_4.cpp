#include <iostream>
#include "Header.h"

using namespace std;


int main() {
    bool ready = true;
    while (ready) {
        setlocale(0, "rus");
        int k;
        double eps;

        cout << "Task 1" << endl;
        k = 1;
        eps = 0.000001;
        cout << "k=" << k << " eps=" << eps << endl;
        newton(eps, k);
        des_2(k, eps);
        des_3(k, eps);
        cout << endl << endl;

        cout << "Task 2" << endl;
        eps = 0.00000001;
        cout << "k=" << k << " eps=" << eps << endl;
        newton(eps, k);
        des_2(k, eps);
        des_3(k, eps);
        cout << endl << endl;

        cout << "Task 3" << endl;
        k = 10;
        eps = 0.000001;
        cout << "k=" << k << " eps=" << eps << endl;
        newton(eps, k);
        des_2(k, eps);
        des_3(k, eps);
        cout << endl << endl;

        cout << "Task 4" << endl;
        k = 10;
        eps = 0.00000001;
        cout << "k=" << k << " eps=" << eps << endl;
        newton(eps, k);
        des_2(k, eps);
        des_3(k, eps);
        cout << endl << endl;


        cout << "Хотети продолжить? (0/1): ";
        cin >> ready;
    }
}
