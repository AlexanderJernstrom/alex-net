#include "regression/linear_regression.h"
#include <stdio.h>
#include <stdlib.h> // pulls in declaration of malloc, free

// 1 2 3
// 4 5 6

// 7 8
// 9 10
// 11 12

int main()
{

    double xValues[] = {1, 2, 3, 4, 5};
    double yValues[] = {4, 7, 8, 10, 11};

    double *result = linearRegression(xValues, yValues, 5);

    // print out result
    printf("K value: %f and M value: %f\n", result[0], result[1]);

    // print the dimensiosn of the matrix

    // printf("k = %f\n", simpleLinReg(xValues, yValues, 5));

    return 0;
}