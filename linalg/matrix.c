#include <stdio.h>;

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