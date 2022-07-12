// Copyright 2021 Dmitriy dimapermyakov55@gmail.com

#include "Header.h"

void Fill(long double** arr, size_t m, size_t n) {
  // int a[] = {2, 5, 7, 3, 9, 15, 5, 16, 20};
  bool putting;
  cout << "Ðó÷íîé ââîä èëè ðàíäîì (1|0): ";
  cout << "\x1b[35m";
  cin >> putting;
  cout << "\x1b[0m";

  size_t t = 0;
  for (size_t i = 0; i < m; i++) {
    for (size_t j = 0; j < n; j++) {
      if (!putting)
        arr[i][j] = rand() % 100;

      else {
        cout << " array [" << i << "][" << j << "] = ";
        cout << "\x1b[35m";
        cin >> arr[i][j];
        cout << "\x1b[0m";
      }

      // çàäà÷à èç âîðäà äëÿ ïðîâåðêè
      // arr[i][j] = a[t++];
    }
  }
}

bool StraightCourse(long double** arr, long double** arr1, size_t m, size_t n,
                    bool typeMatrix, size_t precision) {
  cout << "\x1b[34m============== Ïðÿìîé õîä ==============\x1b[0m\n\n";
  for (size_t i = 0; i < m; i++) {
    long double k = arr[i][i];
    if (k == 0) {
      // åñëè k=0 íà äèàãîíàëå, èä¸ì ïî ñòîëáöó â ïîèñêàõ k!=0
      size_t help = 0;
      size_t cheating = 0;
      while (arr[help][i] == 0 && help < m) {
        if (help == m - 1) {
          cout << "\x1b[31mÎáðàòíàÿ ìàòðèöà íå ñóùåñòâóåò\x1b[0m\n";
          return 0;
        }
        ++help;
        ++cheating;
      }

      if (cheating == 0) {
        cout << "\x1b[31mÎáðàòíàÿ ìàòðèöà íå ñóùåñòâóåò\x1b[0m\n";
        return 0;
      }
      // åñëè íàõîäèì k != 0, ìåíÿåì ýòó ñòðî÷êó ñî ñòðîêîé ãäå k=0 íà äèàãîíàëå
      for (size_t i2 = 0; i2 < m; i2++) {
        swap(arr[i][i2], arr[help][i2]);
        swap(arr1[i][i2], arr1[help][i2]);
      }
      PrintArr(arr, m, n, typeMatrix, precision);
      k = arr[i][i];
    }

    // äåëèì ñòðîêó íà arr[i][i]
    for (size_t j = 0; j < n; j++) {
      arr[i][j] /= k;
      arr1[i][j] /= k;
    }

    // ñêëàäûâàåì ñòðîêè
    for (size_t z = i + 1; z < m; z++) {
      long double k = arr[z][i];
      for (size_t ind = 0; ind < n; ind++) {
        arr[z][ind] += k * (-1) * arr[i][ind];
        arr1[z][ind] += k * (-1) * arr1[i][ind];
      }
    }
    PrintArr(arr, m, n, typeMatrix, precision);
  }
  cout << endl;
  return 1;
}

void BackCourse(long double** arr, long double** arr1, size_t m, size_t n,
                bool typeMatrix, size_t precision) {
  cout << "\x1b[34m============== Îáðàòíûé õîä ==============\x1b[0m\n\n";
  for (size_t i = m - 1; i > 0; i--) {
    long double k = arr[i][i];

    for (size_t j = n - 1; j > 0; j--) {
      arr[i][j] /= k;
      arr1[i][j] /= k;
    }

    for (int z = i - 1; z > -1; z--) {
      long double k = arr[z][i];
      for (int ind = n - 1; ind > -1; ind--) {
        arr[z][ind] += k * (-1) * arr[i][ind];
        arr1[z][ind] += k * (-1) * arr1[i][ind];
      }
    }
    PrintArr(arr, m, n, typeMatrix, precision);
  }
  cout << endl;
}

void FillUnit(long double** arr, size_t m, size_t n) {
  for (size_t i = 0; i < m; i++) {
    for (size_t j = 0; j < n; j++) {
      if (i == j)
        arr[i][j] = 1;

      else
        arr[i][j] = 0;
    }
  }
}

void Multiplication(long double** arr_old, long double** arr, size_t m,
                    size_t n, bool typeMatrix, size_t precision) {
  cout << "\n\n\x1b[34m************* Óìíîæåíèå ìàòðèö *************\x1b[0m\n\n";
  long double** c = new long double*[m];
  for (int i = 0; i < m; i++) {
    c[i] = new long double[n];
    for (size_t j = 0; j < n; j++) {
      c[i][j] = 0;
      for (size_t k = 0; k < n; k++) c[i][j] += arr_old[i][k] * arr[k][j];
    }
  }

  PrintArr(c, m, n, typeMatrix, precision);
  for (size_t i = 0; i < m; i++) delete[] c[i];
  delete[] c;
}

void PrintArr(long double** arr, size_t rows, size_t cols, bool typeMatrix,
              size_t precision) {
  size_t length_row;
  if (typeMatrix)
    length_row = precision + 8;
  else if (!typeMatrix)
    length_row = precision + 3;
  size_t cols_new = 81 / length_row;
  size_t printed_cols = 0;
  while (printed_cols < cols) {
    for (size_t i = 0; i < rows; ++i) {
      for (size_t j = 0; j < cols_new; ++j) {
        if (typeMatrix) {
          if (arr[i][j + printed_cols] < 0)
            cout << scientific << setprecision(precision)
                 << arr[i][j + printed_cols] << "   ";

          else
            cout << scientific << setprecision(precision) << ' '
                 << arr[i][j + printed_cols] << "   ";

          if (printed_cols + j == cols - 1) break;
        }

        else if (!typeMatrix) {
          if (arr[i][j + printed_cols] < 0)
            cout << fixed << setprecision(precision) << arr[i][j + printed_cols]
                 << "   ";

          else
            cout << fixed << setprecision(precision) << ' '
                 << arr[i][j + printed_cols] << "   ";

          if (printed_cols + j == cols - 1) break;
        }
      }
      cout << endl;
    }
    printed_cols += cols_new;

    for (size_t i = 0; i < 83; i++) cout << '_';
    cout << endl << endl;
  }
}

size_t GetDataInt() {
  // ïðîâåíðêà ââåä¸ííûõ äàííûõ
  while (true) {
    size_t a;
    cout << "\x1b[35m";
    cin >> a;
    cout << "\x1b[0m";
    if (cin.fail()) {
      cin.clear();
      cin.ignore(32767, '\n');
      cout << "\x1b[31mÏðîâåðüòå ââåä¸ííûå äàííûå: \x1b[0m";
    }

    else {
      cin.ignore(32767, '\n');
      return a;
    }
  }
}
