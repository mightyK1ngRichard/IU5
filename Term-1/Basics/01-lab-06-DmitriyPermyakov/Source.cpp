#include "Header.h"

double F1(double x) {
    return x;
}

double F2(double x) {
    return sin(22 * x);
}

double F3(double x) {
    return x * x * x * x;
}

double F4(double x) {
    return atan(x);
}

double F5(double x) // ��� �������
{
    return x * x * x * x * x;
}

double Exactness_F1() {
    return (B * B - A * A) / 2.0;
}

double Exactness_F2() {
    return (cos(A * 22.0) - cos(B * 22.0)) / 22.0;
}

double Exactness_F3() {
    return (B * B * B * B * B - A * A * A * A * A) / 5.0;
}

double Exactness_F4() {
    return B * atan((double) B) - A * atan((double) A) - (log(B * B + 1) - log(A * A + 1)) / 2.0;
}

double Exactness_F5() {
    return (B * B * B * B * B * B - A * A * A * A * A * A) / 6.0;
}

double rectangle(TPF F, double a, double b, double eps, int &n) {
    n = 2;
    double s_old = 0, s_new = 0, dx;

    dx = (b - a) / n;
    for (size_t i = 0; i <= n; i++)
        s_old += dx * F(a + (i - 0.5) * dx);

    do {
        s_new = s_old;
        n *= 2;
        s_old = 0;
        dx = (b - a) / n;
        for (size_t i = 0; i <= n; i++)
            s_old += dx * F(a + (i - 0.5) * dx);

    } while (fabs(s_old - s_new) > eps);
    return s_old;
}

double trapeze(TPF F, double a, double b, double eps, int &n) {
    n = 1;
    double dx = (b - a) / n;
    double sum = 0, sumNew = 0;

    for (size_t step = 0; step < n; step++) {
        double x1 = a + step * dx;
        double x2 = a + (step + 1) * dx;
        sum += 0.5 * (x2 - x1) * (F(x1) + F(x2));
    }
    do {
        sumNew = sum;
        sum = 0;
        n *= 2;
        dx = (b - a) / n;
        for (size_t step = 0; step < n; step++) {
            double x1 = a + step * dx;
            double x2 = a + (step + 1) * dx;
            sum += 0.5 * (x2 - x1) * (F(x1) + F(x2));
        }
    } while (fabs(sumNew - sum) > eps);
    return sum;
}

void PrintTabl(INTEGRALS i_prn[], int k) {
    const int m = 4;//����� �������� �������
    int wn[m] = {12, 18, 18, 10};//������ �������� �������
    char title[m][20] = {"Function", "Integral", "IntSum", "N "};
    int size[m];
    for (int i = 0; i < m; i++)
        size[i] = strlen(title[i]);
    //����� �������
    cout << char(218) << setfill(char(196));
    for (int j = 0; j < m - 1; j++)
        cout << setw(wn[j]) << char(194);
    cout << setw(wn[m - 1]) << char(191) << endl;

    cout << char(179);
    for (int j = 0; j < m; j++)
        cout << setw((wn[j] - size[j]) / 2) << setfill(' ') << ' ' << title[j]
             << setw((wn[j] - size[j]) / 2) << char(179);
    cout << endl;

    //���������� �������
    for (int i = 0; i < k; i++) {
        cout << char(195) << fixed;
        for (int j = 0; j < m - 1; j++)
            cout << setfill(char(196)) << setw(wn[j]) << char(197);
        cout << setw(wn[m - 1]) << char(180) << setfill(' ') << endl;

        cout << char(179) << setw((wn[0] - strlen(i_prn[i].name)) / 2) << ' ' << i_prn[i].name
             << setw((wn[0] - strlen(i_prn[i].name)) / 2) << char(179);
        cout << setw(wn[1] - 1) << setprecision(10) << i_prn[i].i_toch << char(179)
             << setw(wn[2] - 1) << i_prn[i].i_sum << setprecision(6) << char(179)
             << setw(wn[3] - 1) << i_prn[i].n << char(179) << endl;
    }
    //��� �������
    cout << char(192) << setfill(char(196));
    for (int j = 0; j < m - 1; j++)
        cout << setw(wn[j]) << char(193);
    cout << setw(wn[m - 1]) << char(217) << setfill(' ') << endl;
}
