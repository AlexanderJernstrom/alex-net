#include "regression/linear_regression.h"
#include <math.h>
#include "knn/knn.h"
#include "regression/logistic_regression.h"
#include "functions/loss_functions.h"
#include "linalg/matrix.h"
#include "nn/model/nn.h"
#include "nn/model/layers.h"
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

    // Logistic regression tests
    double xValuesLogistic[] = {500, 480, 550, 530, 520, 480, 400};
    double yValuesLogistic[] = {1, 0, 1, 1, 1, 0, 0};
    // Feature scaling
    /* double meanX = 0;
    double stdDevX = 0;

    double scaledXValues[7] = {};
    for (int i = 0; i < 7; i++)
    {
        meanX += xValuesLogistic[i];
    }
    meanX = meanX / 7;
    for (int i = 0; i < 7; i++)
    {
        stdDevX += (xValuesLogistic[i] - meanX) * (xValuesLogistic[i] - meanX);
    }
    stdDevX = sqrt(stdDevX / 7);

    for (int i = 0; i < 7; i++)
    {
        scaledXValues[i] = (xValuesLogistic[i] - meanX) / stdDevX;
    }

    for (int i = 0; i < 7; i++)
    {
        printf("Scaled value: %f, Mean: %f, StdDev: %f \n", scaledXValues[i], meanX, stdDevX);
    }

    double *logisticResult = logisticRegression(scaledXValues, yValuesLogistic, 7);
    printf("Class: %d\n", results[0]);

    // print out result
    printf("K value: %f and M value: %f\n", result[0], result[1]);

    printf("a value: %f and b value: %f\n", logisticResult[0], logisticResult[1]);
    printf("logistic funtction value: %f", logisticFunction(495, 1.9559, -958.8844)); */

    // print the dimensiosn of the matrix

    // printf("k = %f\n", simpleLinReg(xValues, yValues, 5));
    // For point(450, 0)

    double observed = 0;
    double predicted = logisticFunction(450, 1, -450);
    double deltaPred = logisticFunction(450, 1 + 0.01, -450);

    double loss = pointLogLoss(observed, predicted);
    double aLoss = pointLogLoss(observed, deltaPred);
    // Neural nets
    struct NeuralNet nn = initializeNN(1, 3, 3);

    struct Matrix input_matrix = createMatrix(3, 1);
    setMatrix(&input_matrix, 0, 0, 1);
    setMatrix(&input_matrix, 1, 0, 2);
    setMatrix(&input_matrix, 2, 0, -10);
    printMatrix(input_matrix);
    denseLayer(&input_matrix);
    printf("After dense\n");
    printMatrix(input_matrix);

    struct Matrix input_matrix1 = createMatrix(3, 1);
    setMatrix(&input_matrix1, 0, 0, 1);
    setMatrix(&input_matrix1, 1, 0, 2);
    setMatrix(&input_matrix1, 2, 0, -10);

    struct Matrix second_matrix = createMatrix(3, 3);
    setMatrix(&second_matrix, 0, 0, 2);
    setMatrix(&second_matrix, 0, 1, 2);
    setMatrix(&second_matrix, 0, 2, 2);
    setMatrix(&second_matrix, 1, 0, 2);
    setMatrix(&second_matrix, 1, 1, 2);
    setMatrix(&second_matrix, 1, 2, 2);
    setMatrix(&second_matrix, 2, 0, 2);
    setMatrix(&second_matrix, 2, 1, 2);
    setMatrix(&second_matrix, 2, 2, 2);

    struct Matrix matMulRes = createMatrix(3, 1);

    matMul(&second_matrix, &input_matrix1, &matMulRes);
    printMatrix(matMulRes);
    //    printNN(nn);
    // layers: {denseLayer, reluLayer, denseLayer, sigmoidLayer}
    return 0;
}
