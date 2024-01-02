#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "../functions/loss_functions.h"
#include "../calc/calculus.h"
#include "logistic_regression.h"

double *logisticRegression(double xValues[], double yValues[], int n)
{
    double epsilon = pow(10, -15);
    double a = 0;
    double b = 0;
    double learningRate = 0.1;
    int iter = 0;
    double error = 10;
    double dA = 0;
    double dB = 0;
    // Can be increased here
    while (iter < 5000)
    {
        double *predicted = malloc(n * sizeof(double *));
        for (int i = 0; i < n; i++)
        {
            predicted[i] = fmax(fmin(logisticFunction(xValues[i], a, b), 1 - epsilon), epsilon);
            yValues[i] = fmax(fmin(yValues[i], 1 - epsilon), epsilon);
            //   printf("pred: %f \n", predicted[i]);
        }
        error = logLoss(yValues, predicted, n, a, b);
        for (int i = 0; i < n; i++)
        {
            double deltaALogLoss = pointLogLoss(yValues[i], logisticFunction(xValues[i], a + 0.01, b));
            double deltaBLogLoss = pointLogLoss(yValues[i], logisticFunction(xValues[i], a, b + 0.01));
            double currLoss = pointLogLoss(yValues[i], predicted[i]);
            dA += derivative(deltaALogLoss, currLoss);
            dB += derivative(deltaBLogLoss, currLoss);
        }
        dA = dA / n;
        dB = dB / n;

        a -= (dA * learningRate);
        b -= (dB * learningRate);

        // printf("Iteration: %d, dA: %f, dB: %f, a: %f, b: %f, error: %f \n", iter, dA, dB, a, b, error);
        iter += 1;
    }
    printf("Cost: %f", error);
    double *result = malloc(sizeof(double *));
    result[0] = a;
    result[1] = b;
    return result;
}

double logisticFunction(double x, double a, double b)
{
    double epsilon = pow(10, -15);
    double coeffs = (a * x) + b;
    double denominator = exp(-coeffs) + 1;
    double result = 1 / denominator;
    return fmax(fmin(result, 1 - epsilon), epsilon);
}
