double mse(double x[], double y[], int n, double slope)
{
    double sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += (y[i] - (slope * x[i])) * (y[i] - (slope * x[i]));
    }
    return sum / n;
}

double meanSquaredError(double observed[], double predicted[], int n)
{
    double sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += (observed[i] - predicted[i]) * (observed[i] - predicted[i]);
    }
    return sum / n;
}

double pointMSE(double observed, double predicted)
{
    return (observed - predicted) * (observed - predicted);
}
