#ifndef LOGISTIC_REGRESSION_H
#define LOGISTIC_REGRESSION_H

// Fit 1/(1+e^-(a+bx))
// Maximize likelihood function: log(L(β))=∑ i=1N
double *logisticRegression(double xValues[], double yValues[], int n);
double logisticFunction(double x, double a, double b);

#endif