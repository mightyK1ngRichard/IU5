#include "Header.h"

int main() {
    double a = -1, b = 3;
    int n = 2;
    INTEGRALS integrals[SIZE]{};
    TPF functions[] = {F1, F2, F3, F4, F5};
    TPFEV func_toch[] = {Exactness_F1, Exactness_F2, Exactness_F3, Exactness_F4, Exactness_F5};
    char *func_names[] = {NAME1, NAME2, NAME3, NAME4, NAME5};

    for (size_t i = 0; i < SIZE; ++i) {
        integrals[i].name = func_names[i];
        integrals[i].i_toch = func_toch[i]();
    }

    cout << "\x1b[31m Method of rectangle \x1b[0m\n";
    double eps = 0.01;
    while (eps > 0.000001) {
        cout << "\x1b[34m" << "eps = " << eps << "\x1b[0m\n";
        for (size_t i = 0; i < SIZE; ++i) {
            integrals[i].i_sum = rectangle(functions[i], a, b, eps, n);
            integrals[i].n = n;
        }
        eps *= 0.1;
        PrintTabl(integrals, SIZE);
    }

    cout << "\x1b[31m Method of trapeze \x1b[0m \n";
    eps = 0.01;
    while (eps > 0.000001) {
        cout << "\x1b[34m" << "eps = " << eps << "\x1b[0m\n";
        for (size_t i = 0; i < SIZE; i++) {
            integrals[i].i_sum = trapeze(functions[i], a, b, eps, n);
            integrals[i].n = n;
        }
        eps *= 0.1;
        PrintTabl(integrals, SIZE);
    }
    return 27;
}
