#include <math.h>
#include <stdlib.h>
#include "../functions/loss_functions.h"
#include "../calc/calculus.h"
#include "logistic_regression.h"

double *logisticRegression(double xValues[], double yValues[], int n)
{
    double a = 1;
    double b = 0.0;
    double learningRate = 0.01;
    int iter = 0;
    double error = 10;
    double dA = 0;
    double dB = 0;

    while (iter < 2000)
    {
        double *predicted = malloc(n * sizeof(double *));
        for (int i = 0; i < n; i++)
        {
            predicted[i] = logisticFunction(xValues[i], a, b);
        }
        error = logLoss(yValues, predicted, n, a, b);
        for (int i = 0; i < n; i++)
        {
            dA += derivative(pointLogLoss(yValues[i], logisticFunction(xValues[i], a + 0.01, b), a, b), pointLogLoss(yValues[i], logisticFunction(xValues[i], a, b), a, b));
            dB += derivative(pointLogLoss(yValues[i], logisticFunction(xValues[i], a, b + 0.01), a, b), pointLogLoss(yValues[i], logisticFunction(xValues[i], a, b), a, b));
        }

        dA = dA / n;
        dB = dB / n;

        a -= (dA * learningRate);
        b -= (dB * learningRate);

        iter += 1;
    }
    double *result = malloc(sizeof(double *));
    result[0] = a;
    result[1] = b;
    return result;
}

double logisticFunction(double x, double a, double b)
{
    double coeffs = (a * x) + b;
    double denominator = exp(-coeffs) + 1;
    return 1 / denominator;
}
