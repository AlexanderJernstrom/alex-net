#ifndef MATRIX_H
#define MATRIX_H

struct Matrix
{
    double *elements;
    int rows;
    int cols;
};

double getVal(struct Matrix *matrix, int row, int col);
struct Matrix createMatrix(int rows, int cols);
void setMatrix(struct Matrix *matrix, int row, int col, double value);
void matMul(struct Matrix *matrixA, struct Matrix *matrixB, struct Matrix *out);
void printMatrix(struct Matrix m);
void matAdd(struct Matrix *matrixA, struct Matrix *matrixB, struct Matrix *out);

#endif