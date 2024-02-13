#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#include <assert.h>

double getVal(struct Matrix *matrix, int row, int col)
{
    int index = (row * matrix->cols) + col;
    return matrix->elements[index];
};

struct Matrix createMatrix(int rows, int cols)
{
    double *matrix = malloc(sizeof(double) * (cols * rows));
    struct Matrix m = {.cols = cols, .rows = rows, .elements = matrix};
    return m;
}
void setMatrix(struct Matrix *matrix, int row, int col, double value)
{
    int index = (row * matrix->cols) + col;
    matrix->elements[index] = value;
}

void printMatrix(struct Matrix m)
{
    printf("Printing matrix with dimensions: %d x %d", m.rows, m.cols);
    for (int i = 0; i < (m.cols * m.rows); i++)
    {
        printf("Value: %f \n", m.elements[i]);
    }
}

void matAdd(struct Matrix *matrixA, struct Matrix *matrixB, struct Matrix *out)
{
    if ((matrixA->cols * matrixA->rows) == (matrixB->cols * matrixB->rows))
    {

        for (int i = 0; i < (matrixA->cols * matrixA->rows); i++)
        {
            out->elements[i] = matrixA->elements[i] + matrixB->elements[i];
        }
    }
}

struct Matrix extractVector(struct Matrix *data, int col)
{
    struct Matrix vector = createMatrix(data->rows, 1);
    for (int i = 0; i < data->rows; i++)
    {
        setMatrix(&vector, i, 0, getVal(&vector, i, col));
    }
    return vector;
}

struct Matrix *deepCopyMatrix(const struct Matrix *original)
{
    // Allocate memory for the new matrix
    struct Matrix *copy = malloc(sizeof(struct Matrix));
    if (copy == NULL)
    {
        return NULL; // Memory allocation failed
    }

    // Copy rows and cols
    copy->rows = original->rows;
    copy->cols = original->cols;

    // Allocate memory for the elements
    copy->elements = malloc(sizeof(double) * copy->rows * copy->cols);
    if (copy->elements == NULL)
    {
        free(copy);  // Free the previously allocated memory
        return NULL; // Memory allocation failed
    }

    // Copy the elements
    for (int i = 0; i < copy->rows * copy->cols; i++)
    {
        copy->elements[i] = original->elements[i];
    }

    return copy;
}

void matMul(struct Matrix *matrixA, struct Matrix *matrixB, struct Matrix *out)
{

    int n = matrixA->cols;
    int m = matrixA->rows;
    int p = matrixB->cols;

    struct Matrix out_matrix = createMatrix(matrixA->rows, matrixB->cols);

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < p; j++)
        {
            double sum = 0;

            for (int k = 0; k < n; k++)
            {
                sum = sum + (getVal(matrixA, i, k) * getVal(matrixB, k, j));
            }
            setMatrix(&out_matrix, i, j, sum);
        }
    }
    out->cols = out_matrix.cols;
    out->rows = out_matrix.rows;
    out->elements = out_matrix.elements;
};

struct Matrix transpose(struct Matrix *matrix)
{

    struct Matrix *transposedMatrix = deepCopyMatrix(matrix);
    transposedMatrix->cols = matrix->rows;
    transposedMatrix->rows = matrix->cols;
    return *transposedMatrix;
}