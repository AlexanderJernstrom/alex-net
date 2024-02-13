#ifndef ACTIVATION_FUNCTIONS_H
#define ACTIVATION_FUNCTIONS_H
double relU(double x);
double sigmoid(double x);
double softplus(double x);
double dSigmoid(double x);
double dReLU(double x);
struct Matrix softmax(struct Matrix m);
#endif