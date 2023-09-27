#include "regression/linear_regression.h"
#include "knn/knn.h"
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

    struct knnPoint classifiedPoints1;
    classifiedPoints1.class = 0;
    classifiedPoints1.dim = 1;

    // allocate memory for coords
    classifiedPoints1.coords = (double *)malloc(1 * sizeof(double));
    if (classifiedPoints1.coords == NULL)
    {
        // handle error
        return 1;
    }

    // initialize the array
    classifiedPoints1.coords[0] = 0.0;

    struct knnPoint classifiedPoints2;
    classifiedPoints2.class = 0;
    classifiedPoints2.dim = 1;

    // allocate memory for coords
    classifiedPoints2.coords = (double *)malloc(1 * sizeof(double));
    if (classifiedPoints2.coords == NULL)
    {
        // handle error
        return 1;
    }
    classifiedPoints2.coords[0] = 1.0;

    struct knnPoint classifiedPoints3;
    classifiedPoints3.class = 1;
    classifiedPoints3.dim = 1;

    // allocate memory for coords
    classifiedPoints3.coords = (double *)malloc(1 * sizeof(double));
    if (classifiedPoints3.coords == NULL)
    {
        // handle error
        return 1;
    }
    classifiedPoints3.coords[0] = 2.0;

    struct knnPoint classifiedPoints4;
    classifiedPoints4.class = 1;
    classifiedPoints4.dim = 1;

    // allocate memory for coords
    classifiedPoints4.coords = (double *)malloc(1 * sizeof(double));
    if (classifiedPoints4.coords == NULL)
    {
        // handle error
        return 1;
    }
    classifiedPoints4.coords[0] = 3.0;

    struct knnPoint classifiedPoints[4] = {classifiedPoints1, classifiedPoints2, classifiedPoints3, classifiedPoints4};

    struct Point unclassified1;
    unclassified1.dim = 1;
    unclassified1.coords = (double *)malloc(1 * sizeof(double));
    if (classifiedPoints3.coords == NULL)
    {
        // handle error
        return 1;
    }
    unclassified1.coords[0] = 1.1;

    struct Point unclassified[] = {unclassified1};

    int *results = kNearestNeighbors(3, classifiedPoints, unclassified, 1, 4);

    printf("Class: %d\n", results[0]);

    // print out result
    printf("K value: %f and M value: %f\n", result[0], result[1]);

    // print the dimensiosn of the matrix

    // printf("k = %f\n", simpleLinReg(xValues, yValues, 5));

    return 0;
}