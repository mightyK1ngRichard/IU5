#include "Header.h"

using namespace std;

int main() {
    srand(time(NULL));
    setlocale(0, "rus");
    size_t m, n, precision;
    cout << "Введите m = ";
    m = GetDataInt();
    cout << "Введите n = ";
    n = GetDataInt();
    bool typeMatrix = 0;
    // cout << "Тип матрицы: scientific or fixed (1/0): \x1b[35m";
    // cin >> typeMatrix;
    cout << "\x1b[0mВведите точность. Precision = ";
    precision = GetDataInt();

    if (m != n) {
        cout << "\x1b[31mm != n, матрица не существует! \x1b[0m\n";
        return 0;
    }

    // создаем двумерные массивы
    long double **arr = new long double *[m];
    long double **arr1 = new long double *[m];
    long double **arr_old = new long double *[m];
    for (size_t i = 0; i < m; i++) {
        arr[i] = new long double[n];
        arr1[i] = new long double[n];
        arr_old[i] = new long double[n];
    }

    Fill(arr, m, n);
    FillUnit(arr1, m, n);
    cout << "\x1b[31m\n\n*-*-*-*-*-*-*- Начальная матрица "
            "-*-*-*-*-*-*-*\x1b[0m\n\n";
    PrintArr(arr, m, n, typeMatrix, precision);

    // копируем начальную матрицу в новый массив
    for (size_t i = 0; i < m; i++) {
        for (size_t j = 0; j < n; j++) arr_old[i][j] = arr[i][j];
    }
    cout << endl;

    bool ok = StraightCourse(arr, arr1, m, n, typeMatrix, precision);

    // если матрица не существует, прекращаем работу
    if (!ok) return 0;

    BackCourse(arr, arr1, m, n, typeMatrix, precision);

    cout << "\x1b[31m\n\n*-*-*-*-*-*-*- Обратная матрица "
            "-*-*-*-*-*-*-*\x1b[0m\n\n";
    PrintArr(arr1, m, n, typeMatrix, precision);

    // проверка
    Multiplication(arr_old, arr1, m, n, typeMatrix, precision);
    for (size_t i = 0; i < m; i++) {
        delete[] arr[i];
        delete[] arr1[i];
        delete[] arr_old[i];
    }
    delete[] arr;
    delete[] arr1;
    delete[] arr_old;
    return 0;
}
