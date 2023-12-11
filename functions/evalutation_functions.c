
double r2Score(double *y, double *y_pred, int n)
{
    double sumOfSquaresRegression = 0;
    double totalSumOfSquares = 0;

    double yAverage = 0;

    for (int i = 0; i < n; i++)
    {
        yAverage = yAverage + y[i];
    }
    yAverage = yAverage / n;

    for (int i = 0; i < n; i++)
    {
        sumOfSquaresRegression = sumOfSquaresRegression + ((y[i] - y_pred[i]) * (y[i] - y_pred[i]));
        totalSumOfSquares = totalSumOfSquares + ((y[i] - yAverage) * (y[i] - yAverage));
    }

    return 1 - (sumOfSquaresRegression / totalSumOfSquares);
}