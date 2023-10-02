#include <math.h>
#include "../functions/loss_functions.h"
#include "../calc/calculus.h"

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
        error = logLoss(yValues, xValues, n, a, b);

                iter += 1;
    }

    return 1;
}

double logisticFunction(double x, double a, double b)
{
    return 1.0 / (1.0 + exp((-a * x) - b));
}
