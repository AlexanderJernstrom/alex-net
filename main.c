#include <stdio.h>
#include <stdlib.h> // pulls in declaration of malloc, free

double derivative(double x1, double x2);
double simpleLinReg(double xValues[], double yValues[], int n);
double mse(double x[], double y[], int n, double slope);
double **linearRegression(double xValues[], double yValues[], int n);
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

// Function to allocate a square matrix of size n
double **allocateMatrix(int n)
{
    double **matrix = malloc(n * sizeof(double *));
    for (int i = 0; i < n; i++)
    {
        matrix[i] = malloc(n * sizeof(double));
    }
    return matrix;
}

// Function to free a square matrix of size n
void freeMatrix(double **matrix, int n)
{
    for (int i = 0; i < n; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
}

double **matInv(double **matrix, int n)
{
    double **augmented = allocateMatrix(n);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            augmented[i][j] = matrix[i][j];
        }
    }

    // Allocate memory for identity matrix
    double **identity = allocateMatrix(n);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            identity[i][j] = (i == j) ? 1.0 : 0.0;
        }
    }

    // Perform Gaussian Elimination
    for (int i = 0; i < n; i++)
    {
        // Make the diagonal contain all 1's
        double diag = augmented[i][i];
        if (diag == 0)
        {
            // Need to swap with a row below that has a non-zero i-th element
            for (int j = i + 1; j < n; j++)
            {
                if (augmented[j][i] != 0)
                {
                    // Swap rows i and j
                    double *temp = augmented[i];
                    augmented[i] = augmented[j];
                    augmented[j] = temp;
                    break;
                }
            }
            diag = augmented[i][i];
            if (diag == 0)
            {
                // This means that the matrix is singular and non-invertible
                freeMatrix(augmented, n);
                freeMatrix(identity, n);
                return NULL;
            }
        }

        for (int j = 0; j < n; j++)
        {
            augmented[i][j] /= diag;
            identity[i][j] /= diag;
        }

        // Make all elements below and above i-th diagonal to be zero
        for (int j = 0; j < n; j++)
        {
            if (i != j)
            {
                double factor = augmented[j][i];
                for (int k = 0; k < n; k++)
                {
                    augmented[j][k] -= factor * augmented[i][k];
                    identity[j][k] -= factor * identity[i][k];
                }
            }
        }
    }

    freeMatrix(augmented, n);
    return identity;
}

// Linear regression, fits a line to data, returns slope and y-intercept [slope, y-intercept]
double **linearRegression(double xValues[], double yValues[], int n)
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

    double **matrix1 = malloc(2 * sizeof(double));
    matrix1[0] = malloc(sizeof(double));
    matrix1[1] = malloc(sizeof(double));
    matrix1[0][0] = xyProductSum;
    matrix1[1][0] = ySum;

    double **matrix2 = allocateMatrix(2);
    matrix2[0][0] = xSquaredSum;
    matrix2[0][1] = xSum;
    matrix2[1][0] = xSum;
    matrix2[1][1] = n;
    double **matrix2Inv = matInv(matrix2, 2);
    freeMatrix(matrix2, 2);

    double **result = matMul(matrix1, matrix2Inv, 1, 2, 2);
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

// 1 2 3
// 4 5 6

// 7 8
// 9 10
// 11 12

int main()
{

    double xValues[] = {1, 2, 3, 4, 5};
    double yValues[] = {2, 4, 6, 8, 10};

    double **result = linearRegression(xValues, yValues, 5);

    // print out result
    for (int i = 0; i < 2; i++)
    {
        printf("%f\n", result[i][0]);
    }

    // print the dimensiosn of the matrix

    // printf("k = %f\n", simpleLinReg(xValues, yValues, 5));

    return 0;
}