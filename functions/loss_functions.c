#include <math.h>
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