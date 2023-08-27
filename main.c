#include <stdio.h>
#include <stdlib.h> // pulls in declaration of malloc, free

double derivative(double x1, double x2);
double simpleLinReg(double xValues[], double yValues[], int n);
double mse(double x[], double y[], int n, double slope);
double *linearRegression(double xValues[], double yValues[], int n);
double **matMul(double **matrix1, double **matrix2, int m, int n, int k);
double **matInv(double **matrix, int n);

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

double **matInv(double **matrix, int n)
{
}

// Linear regression, fits a line to data, returns slope and y-intercept [slope, y-intercept]
double *linearRegression(double xValues[], double yValues[], int n)
{
    if (sizeof(xValues) != sizeof(yValues))
    {
        printf("Error: Dimensions not matching\n");
        return NULL;
    }

    double xSquaredSum = 0.0;
    double xSum = 0.0;
    double xyProductSum = 0.0;
    double ySum = 0.0;

    for (int i = 0; i < n; i++)
    {
        xSquaredSum += xValues[i] * xValues[i];
        xSum += xValues[i];
        xyProductSum += xValues[i] * yValues[i];
        ySum += yValues[i];
    }

    double matrix1[1][1] = {{xyProductSum}, {ySum}};
    double matrix2[2][2] = {{xSquaredSum, xSum}, {xSum, n}};

    double result[2] = {0, 0};
    return result;
}

// Matrix multiplication of MxN with NxK, returns the result of the multiplication
double **matMul(double **matrix1, double **matrix2, int m, int n, int k)
{
    if (sizeof(matrix1[0]) != sizeof(matrix2))
    {
        printf("Error: Matrix dimensions do not match\n");
        return NULL;
    }

    double **result = malloc(m * sizeof(double *));
    for (int i = 0; i < m; i++)
    {
        result[i] = malloc(k * sizeof(double));
    }

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < k; j++)
        {
            result[i][j] = 0;
            for (int l = 0; l < n; l++)
            {
                result[i][j] += matrix1[i][l] * matrix2[l][j];
            }
        }
    }

    return result;
}

int main()
{

    double xValues[] = {1, 2, 3, 4, 5};
    double yValues[] = {2, 4, 6, 8, 10};

    double matrix1[2][3] = {{1, 2, 3}, {4, 5, 6}};
    double matrix2[3][2] = {{7, 8}, {9, 10}, {11, 12}};

    double **stuff = matMul(matrix1, matrix2, 2, 3, 2);
    // print the dimensiosn of the matrix
    printf("Dimensions: %f\n", stuff[0][2]);

    // printf("k = %f\n", simpleLinReg(xValues, yValues, 5));

    return 0;
}