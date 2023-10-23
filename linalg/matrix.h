#ifndef MATRIX_H
#define MATRIX_H

struct Matrix
{
    double *elements;
    int rows;
    int cols;
};

double getVal(struct Matrix *matrix, int row, int col);
struct Matrix createMatrix(int cols, int rows);
void setMatrix(struct Matrix *matrix, int row, int col, double value);
#endif