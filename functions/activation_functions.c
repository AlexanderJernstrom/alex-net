#include <math.h>
double relU(double x)
{
    if (x <= 0)
        return 0;
    if (x >= 0)
        return x;
}

double dReLU(double x)
{
    if (x <= 0)
        return 0;
    if (x >= 0)
        return 1;
}

double sigmoid(double x)
{
    return 1 / (1 + exp(-x));
}

double dSigmoid(double x)
{
    return (sigmoid(x) * (1 - sigmoid(x)));
}

double softplus(double x)
{
    return log(1 + exp(x));
}
