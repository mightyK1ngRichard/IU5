#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int def(int n) {
    int s2 = 1;
    for (int a = 2; a <= n; a++)
        s2 = s2 * a;
    return s2;
}

int main() {
    setlocale(0, "rus");
    int number_prog;
    cout << "Введите номер задания: ";
    cin >> number_prog;
    switch (number_prog) {
        case 1: {
            bool res = true;
            int n, m, k;
            while (res) {
                cout << "Введите значение m: ";
                cin >> m;
                cout << "Введите n (конечное значение цикла for): ";
                cin >> n;
                k = 0;
                for (int i = 5; i <= n; i += 5) {
                    if (i % 5 == 0 && i % m != 0)
                        k += i;
                }

                cout << "Ответ: " << k << endl;
                cout << endl;
                cout << "Вы хотите продолжить? " << endl << "(1 - да / 0 - нет) - ";
                cin >> res;
            }
        }
            break;

        case 2: {
            int n, n1;
            float a, s;
            cout << "Введите a: ";
            cin >> a;

            s = 1;
            if (a >= 0) {
                for (int i = 2; i <= 8; i += 2) {
                    s *= i * i;
                }
                s -= a;
            } else {
                for (int i = 3; i <= 9; i += 3) // цикл for с шагом 3
                {
                    s *= i - 2;
                }
            }

            cout << "При a = " << setprecision(9) << a << ", S = " << s << endl;

        }
            break;

        case 3: {
            cout << setw(3) << 'x' << '|' << setw(11) << 'y' << '|' << setw(11) << 's' << '|' << setw(1) << 'n' << endl;
            double x, y, s, s1, eps = 0.000001;
            int n;
            float start = 0.0;
            float end = 1;
            for (x = start; x <= end; x += 0.2) {
                y = (1 - (x * x / 2)) * cos(x) - ((x * sin(x)) / 2);
                s = 1.0 - ((3 * x * x) / 2);
                n = 1;
                s1 = -((3 * x * x) / 2);
                while (abs(s1) > eps) {
                    n++;
                    s1 = (pow((-1), n) * ((2 * n * n + 1) * (pow(x, 2 * n)))) / (def(2 * n));
                    s += s1;
                }

                if (x == 0) {
                    cout << showpoint << setw(3) << setprecision(2) << x << '|' << setprecision(8) << fixed << setw(11)
                         << y << '|' << setw(11) << setprecision(8) << s << '|' << setw(1) << n << endl;
                } else
                    cout << showpoint << setw(3) << setprecision(1) << x << '|' << setprecision(8) << fixed << setw(11)
                         << y << '|' << setw(11) << setprecision(8) << s << '|' << setw(1) << n << endl;
            }
        }
            break;


        case 4: {
            double s1;
            int m;
            const double s11 = sqrt(4 + sqrt(2));

            bool res = true;
            while (res) {
                s1 = s11;
                cout << "Введите m = ";
                cin >> m;
                if (m == 1) {
                    cout << "y= " << sqrt(2) << endl << endl;
                    break;
                } else {
                    for (int n = 3; n <= m; n++) {
                        s1 = sqrt(2 * n + s1);
                        if (n == 3 || n == 5 || n == 10)
                            cout << "Промежуточное значение при n=" << n << ", y = " << s1 << endl;
                    }
                    cout << endl;
                    cout << "y = " << s1 << endl << endl;
                    cout << "Хочешь продолжить? (1/0): ";
                    cin >> res;
                }
            }
        }
            break;

        default:
            cout << "Sorry, this number wasn't found, pls check the entered data" << endl;
            break;

    }
}
