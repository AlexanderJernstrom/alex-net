#include <math.h>
#include "../linalg/matrix.h"
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

struct Matrix softmax(struct Matrix m)
{
    struct Matrix exponentiated = createMatrix(m.rows, m.cols);
    for (int i = 0; i < (m.cols * m.rows); i++)
    {
        exponentiated.elements[i] = exp(m.elements[i]);
    }

    float exponentiated_sum = 0;
    for (int i = 0; i < (m.cols * m.rows); i++)
    {
        exponentiated_sum = exponentiated_sum + exponentiated.elements[i];
    }

    for (int i = 0; i < (m.cols * m.rows); i++)
    {
        exponentiated.elements[i] = exponentiated.elements[i] / exponentiated_sum;
    }
    return exponentiated;
}

double softplus(double x)
{
    return log(1 + exp(x));
}
