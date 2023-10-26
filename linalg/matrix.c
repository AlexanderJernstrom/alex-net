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
}

void matMul(struct Matrix *matrixA, struct Matrix *matrixB, struct Matrix *out)
{
    if (matrixA->cols != matrixB->rows || out->rows != matrixA->rows || out->cols == matrixB->cols)
    {
        printf("Wrong dimensions");
    }
    int n = matrixA->cols;
    for (int i = 0; i < matrixA->rows; i++)
    {
        for (int j = 0; j < matrixB->cols; j++)
        {
            double sum = 0;

            for (int k = 0; k < n; k++)
            {
                sum = sum + (getVal(matrixA, i, k) * getVal(matrixB, k, j));
            }
            setMatrix(out, i, j, sum);
        }
    }
};