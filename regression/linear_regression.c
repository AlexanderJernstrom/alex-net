#include <stdio.h>
#include <stdlib.h>
#include "../functions/loss_functions.h"
#include "../calc/calculus.h"
// Extremely simple linear regression: y = kx, calculates k
double simpleLinReg(double xValues[], double yValues[], int n)
{
    double slope = 0;
    double learning_rate = 0.01;
    double error = 10;
    // for each slope, calcualate mse
    // change slope in any given direction
    // stop when mse is minimized
    while (derivative(mse(xValues, yValues, n, slope + learning_rate), error) > 0.1 || derivative(mse(xValues, yValues, n, slope + learning_rate), error) < -0.1)
    {
        error = mse(xValues, yValues, n, slope);
        // print error
        printf("error: %f\n", error);
        if (error > mse(xValues, yValues, n, slope + learning_rate))
        {
            slope += learning_rate;
        }
        else if (error > mse(xValues, yValues, n, slope - learning_rate))
        {
            slope -= learning_rate;
        }
    }

    return slope;
}

// Linear regression, fits a line to data, returns slope and y-intercept [slope, y-intercept]
double *linearRegression(double xValues[], double yValues[], int n)
{
    float k = 1;
    float m = 1;
    // y = kx + m
    // error: ((y) - (kx1 + m))^2
    double learning_rate = 0.01;
    double error = 10;
    int iter = 0;
    double dSlope = 0;
    double dIntercept = 0;

    while (iter < 2000)
    {
        double *predicted = malloc(n * sizeof(double *));

        for (int i = 0; i < n; i++)
        {
            predicted[i] = (xValues[i] * k) + m;
        }
        error = meanSquaredError(yValues, predicted, n);

        for (int i = 0; i < n; i++)
        {
            // y = kx + m
            // dSlope = errk(k+h) - err / h
            dSlope += derivative(pointMSE(yValues[i], (xValues[i] * (k + 0.01)) + m), pointMSE(yValues[i], (xValues[i] * k) + m));
            dIntercept += derivative(pointMSE(yValues[i], (xValues[i] * k) + (m + 0.01)), pointMSE(yValues[i], (xValues[i] * k) + m));
        }
        // print dSlope and dIntercept
        dSlope = dSlope / n;
        dIntercept = dIntercept / n;

        k -= (dSlope * learning_rate);
        m -= (dIntercept * learning_rate);

        iter += 1;
    }
    // printf("Iteration: %d. k = %f, m = %f, dK = %f, dM = %f \n", iter, k, m, (dSlope * learning_rate), (dIntercept * learning_rate));

    double *result = malloc(sizeof(double *));
    result[0] = k;
    result[1] = m;
    return result;
}