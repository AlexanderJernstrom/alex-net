#include <math.h>
#include "../linalg/matrix.h"
#include <stdio.h>
#include <stdlib.h>
double mse(double x[], double y[], int n, double slope)
{
    double sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += (y[i] - (slope * x[i])) * (y[i] - (slope * x[i]));
    }
    return sum / n;
}

double meanSquaredError(double observed[], double predicted[], int n)
{
    double sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += (observed[i] - predicted[i]) * (observed[i] - predicted[i]);
    }
    return sum / n;
}

double pointMSE(double observed, double predicted)
{
    return (observed - predicted) * (observed - predicted);
}

double pointMSEDerivative(double observed, double predicted)
{
    return 2 * (observed - predicted);
}

double crossEntropy(int C, struct Matrix x, struct Matrix true_values)
{
    if (C != (true_values.cols * true_values.rows))
    {

        perror("truth values and classes need to be of same length");
        exit(1);
    }
    double loss = 0;
    for (int i = 0; i < C; i++)
    {
        loss += true_values.elements[i] * log(x.elements[i]);
    }
    return -loss;
}

struct Matrix crossEntropyDerivative(int C, struct Matrix *true_values, struct Matrix *predicted_values)
{
    if (true_values->rows != predicted_values->rows)
    {

        printf("cols:%d  rows: %d", predicted_values->cols, predicted_values->rows);
        perror("Predicted and true values must be of same size");
        exit(1);
    }
    struct Matrix gradient = createMatrix(1, true_values->cols);

    for (int i = 0; i < C; i++)
    {
        gradient.elements[i] = -(true_values->elements[i] / predicted_values->elements[i]) + ((1 - true_values->elements[i]) / (1 - predicted_values->elements[i]));
    }

    return gradient;
}

// Reference: https://developers.google.com/machine-learning/crash-course/logistic-regression/model-training
double pointLogLoss(double observed, double predicted)
{
    double logLoss = 0.0;

    logLoss = observed * log(predicted) + (1 - observed) * log(1 - predicted);
    return -logLoss;
}

double logLoss(double observed[], double predicted[], int n, double currA, double currB)
{
    double sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += pointLogLoss(observed[i], predicted[i]);
    }
    return sum / n;
}