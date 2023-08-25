#include <stdio.h>

double derivative(double x1, double x2);
double simpleLinReg(double xValues[], double yValues[], int n);
double mse(double x[], double y[], int n, double slope);

double derivative(double x1, double x2)
{
    return (x1 - x2) / 0.01;
}

double mse(double x[], double y[], int n, double slope)
{
    double sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += (y[i] - (slope * x[i])) * (y[i] - (slope * x[i]));
    }
    return sum / n;
}
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

int main()
{
    printf("Hello World!\n");

    double xValues[] = {1, 2, 3, 4, 5};
    double yValues[] = {2, 4, 6, 8, 10};
    // Should get k = 2
    printf("k = %f\n", simpleLinReg(xValues, yValues, 5));

    return 0;
}