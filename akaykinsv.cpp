﻿#include "akaykinsv.h"

/**
 * Введение в дисциплину
 */
void akaykinsv::lab1()
{
  cout << "Hello World!" << endl;
}


/**
 * Метод Гаусса с выбором главного элемента
 */
void akaykinsv::lab2()
{
    for (int column = 0, row = 0; column < N; column++, row++) {
        int max = row;
        for (int i = row + 1; i < N; i++) {
            if (abs(A[i][column]) > abs(A[max][column])) {
                max = i;
            }
        }

        if (max != row) {
            double swap[N];
            memcpy(swap, A[row], N);
            memcpy(A[row], A[max], N);
            memcpy(A[max], swap, N);
            double bSwap = b[max];
            b[max] = b [row];
            b[row] = bSwap;
        }
        double tmp = A[row][column];
        for (int i = column; i < N; i++) {
            A[row][i] /= tmp;
        }
        b[row] /= tmp;

        for (int i = row + 1; i < N; i++) {
            tmp = A[i][column];
            for (int j = column+1; j < N; j++) {
                A[i][j] -= A[row][j] * tmp;
            }
            b[i] -= b[row] * tmp;
        }
    } // получили треугольную матрицу

    for (int i = N-1, j = N - 1; i >= 0; i--, j--) {

        b[i] /= A[i][j];

        for (int k = i - 1; k >= 0; k--) {
            b[k] -= b[i] * A[k][j];
        }
        x[i] = b[i];
    }


}



/**
 * Метод прогонки
 */
void akaykinsv::lab3()
{
    double alpha[N - 1], beta[N], y[N];
    //Прямая прогонка
    y[0] = A[0][0];
    beta[0] = b[0] / y[0];
    alpha[0] = -A[0][1] / y[0];
    for (int i = 1; i < N; i++) {
        y[i] = A[i][i] + A[i][i-1]*alpha[i-1];
        beta[i] = (b[i] - A[i][i-1]*beta[i-1])/y[i];
        if (i != N - 1) {
            alpha[i] = -A[i][i+1]/y[i];
        }
    }

    //Обратная прогонка
    x[N-1] = beta[N-1];
    for (int i = N-2; i >= 0; i--) {
        x[i] = alpha[i] * x[i+1] + beta[i];
    }
}


/**
 * Метод Холецкого
 */
void akaykinsv::lab4()
{
    double S[N][N];
    int D[N][N];
    for (int i = 0; i < N; i++) {

        double subSum = 0;
        for (int l = 0; l <= i - 1; l++) {
            subSum += S[l][i] * S[l][i] * D[l][l];
        }

        int sign = (A[i][i] - subSum) < 0;
        D[i][i] =  (int)pow(-1, sign);

        S[i][i] = sqrt(abs(A[i][i] - subSum));
        for (int j = 0; j < i; j++) S[i][j] = 0.0;
        for (int j = i+1; j < N; j++) {
            double subSum = 0;
            for (int l = 0; l <= i - 1; l++) subSum += S[l][j] * S[l][i] * D[l][l];
            S[i][j] = (A[i][j] - subSum)/S[i][i]*D[i][i];
        }
        //Обратный ход

        double y[N];
        y[0] = b[0] / S[0][0];
        for (int i = 1; i < N; i++) {
              double subSum = 0;
              for (int j = 0; j <= i - 1; j++) subSum += S[j][i] * y[j];
              y[i] = b[i] - subSum;
              y[i] /= S[i][i];
        }
        x[N - 1] = y[N - 1] / S[N - 1][N - 1];
        for (int i = N - 2; i >=0; i--) {
            double subSum = 0;
            for (int k = i + 1; k <= N - 1; k++) subSum += S[i][k] * x[k];
            x[i] = y[i] - subSum;
            x[i] /= S[i][i];
        }

    }

}



/**
 * Метод Якоби или Зейделя
 */
void akaykinsv::lab5()
{
    double *xk = new double[N];
    double eps = 1e-20;
    double norm;
    //Начальное приближение
    for (int i = 0; i < N; i++) x[i] = b[i]/A[i][i];

    do {
        for (int i = 0; i < N; i++) {

            for (int j = 0; j < N; j++) xk[j] = x[j];

            double lowerSum = 0, upperSum = 0;

            for (int j = 0; j < i; j++) lowerSum += A[i][j] * xk[j];
            for (int j = i + 1; j < N; j++) upperSum += A[i][j] * xk[j];

            x[i] = 1/A[i][i] * (b[i] - lowerSum - upperSum);

            if ( i == 0 ) norm = abs(x[i] - xk[i]);
            if (abs(x[i] - xk[i]) > norm) norm = abs(x[i] - xk[i]);

        }

    } while (norm >= eps);
}



/**
 * Метод минимальных невязок
 */
void akaykinsv::lab6()
{

}



/**
 * Метод сопряженных градиентов
 */
void akaykinsv::lab7()
{

}


/**
 * Метод вращения для нахождения собственных значений матрицы
 */
void akaykinsv::lab8()
{

}


/**
 * Нахождение наибольшего по модулю собственного значения матрицы
 */
void akaykinsv::lab9()
{

}


std::string akaykinsv::get_name()
{
  return "S. V. Akaikin";
}
