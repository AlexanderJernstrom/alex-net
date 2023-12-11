

double derivative(double x1, double x2)
{
    return (x1 - x2) / 0.01;
}

double linearDSlope(double slope, double intercept, double x, double y)
{
    return -2 * (y - (slope * x) - intercept) * x;
}

double linearDIntercept(double slope, double intercept, double x, double y)
{
    return -2 * (y - (slope * x) - intercept);
}