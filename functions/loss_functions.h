#ifndef LOSS_FUNCTIONS_H
#define LOSS_FUNCTIONS_H

double meanSquaredError(double observed[], double predicted[], int n);
double pointMSE(double observed, double predicted);
double mse(double x[], double y[], int n, double slope);
double pointLogLoss(double observed, double predicted);
double logLoss(double observed[], double predicted[], int n, double currA, double currB);

double pointMSEDerivative(double observed, double predicted);
#endif