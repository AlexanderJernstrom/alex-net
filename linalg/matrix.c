#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#include <assert.h>

double getVal(struct Matrix *matrix, int row, int col)
{
    int index = (row * matrix->cols) + col;
    return matrix->elements[index];
};

struct Matrix createMatrix(int cols, int rows)
{
    double *matrix = malloc(sizeof(double *) * (cols * rows));
    struct Matrix m = {.cols = cols, .rows = rows, .elements = matrix};
    return m;
}
void setMatrix(struct Matrix *matrix, int row, int col, double value)
{
    int index = (row * matrix->cols) + col;
    matrix->elements[index] = value;
}