#include "Header.h"

int main() {
    srand(time(NULL));
    // rows- строки, cols- колонки, x- введённое число
    int rows, cols;
    double x = 1;
    std::cout << "Enter the number of \nrows= ";
    std::cin >> rows;
    std::cout << "columns= ";
    std::cin >> cols;


    auto **matrix = new double *[rows];
    for (int i = 0; i < rows; ++i)
        matrix[i] = new double[cols];


    // создаём массив для сумм
    long double *sum = new long double[rows];


    FillArr(matrix, rows, cols, x);
    PrintArr(matrix, rows, cols, x);


    double B[10][10]{0};
    for (size_t i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++)
            B[i][j] = i * 10 + j;
    }


    auto B2 = new double *[10];
    for (size_t i = 0; i < 10; i++)
        B2[i] = B[i];
    std::cout << std::setw(36) << " AARAY B \n";
    PrintArr(B2, 10, 10, x);
    //000000BD0D8FF050

    std::cout << (B + 1) << "      " << sizeof(double) << "        \n";

    /*std::cout    << "  " << *(B + 1) << "  " << B[2] << std::endl;
    std::cout << B[0][45] << "  " << *(B +1)-1<< "  " << *B[4] << std::endl;
    std::cout << *(*(B + 1)) << "  " << B[1] << std::endl;
    std::cout << (B[1] + 1) << "  " << *(*B + 1) << std::endl;
    std::cout << B[2][10] << "  " << *(B[0] + 20) << "  " << *B[2] << std::endl;*/

    // удаляем содержимое динамич массива
    for (int i = 0; i < rows; ++i)
        delete[] matrix[i];
    delete[] matrix;
    delete[] sum;
}