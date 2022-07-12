#include "Header.h"

int fact(int num)
{
    if (num == 1 || num == 0)
        return 1;
    else
        return (fact(num - 1) * num);
}


void FillArr(double** arr, int rows, int cols, int x)
{
    for (int i = 1; i <= rows; ++i)
    {
        for (int j = 1; j <= cols; ++j)
        {
            if (i - 1 == j - 1)
                arr[i - 1][j - 1] = 1;
            else
            {
                if (j - 1 > i - 1)
                    arr[i - 1][j - 1] = pow((-x), i) / (pow((fact(j)), i));

                else
                    arr[i - 1][j - 1] = pow(x, i) / (pow(fact(j), i));
            }
        }
    }
}


void PrintArr(double** arr, int rows, int cols, double x)
{
    size_t precision;
    bool typeMatrix;
    std::cout << "Choose the matrix print type: scientific or fixed (1/0): ";
    std::cin >> typeMatrix;
    std::cout << "Enter the precision of the calculations. Precision = ";
    std::cin >> precision;
    size_t length_row;
    if (typeMatrix)
        length_row = precision + 8;
    else if (!typeMatrix)
        length_row = precision + 3;
    size_t cols_new = 81 / length_row;
    size_t printed_cols = 0;
    while (printed_cols < cols) 
    {
        for (size_t i = 0; i < rows; ++i)
        {
            for (size_t j = 0; j < cols_new; ++j)
            {
                if (typeMatrix)
                {
                    if (arr[i][j + printed_cols] < 0) 
                        std::cout << std::scientific << std::setprecision(precision) << arr[i][j + printed_cols] << "   ";
                    
                    else
                        std::cout << std::scientific << std::setprecision(precision) << ' ' << arr[i][j + printed_cols] << "   ";
                    
                    if (printed_cols + j == cols - 1)
                        break;
                }

                else if (!typeMatrix)
                {
                    if (arr[i][j + printed_cols] < 0)
                        std::cout << std::fixed << std::setprecision(precision) << arr[i][j + printed_cols] << "   ";

                    else
                        std::cout << std::fixed << std::setprecision(precision) << ' ' << arr[i][j + printed_cols] << "   ";

                    if (printed_cols + j == cols - 1)
                        break;

                }
            }
            std::cout << std::endl;
        }
        printed_cols += cols_new;
       
        for (size_t i = 0; i < 83; i++)
            std::cout << '_';
        std::cout << std::endl << std::endl;
    }
}


//void Sort(double** arr, int rows, int cols, long double* sum)
//{
//    long double buf_sum;
//    double buf_a;
//    int min;
//    for (int i = 0; i < rows - 1; i++)
//    {
//        min = i;
//        for (int j = i + 1; j < rows; j++)
//            if (sum[j] < sum[min])
//                min = j;
//
//        buf_sum = sum[i];
//        sum[i] = sum[min];
//        sum[min] = buf_sum;
//
//        for (int j = 0; j < cols; j++)
//        {
//            buf_a = arr[i][j];
//            arr[i][j] = arr[min][j];
//            arr[min][j] = buf_a;
//        }
//    }
//}