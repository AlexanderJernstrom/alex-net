#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "linear_regression_eval.h"
#include "../regression/linear_regression.h"
#include "../functions/evaluation_functions.h"

void extractHousePriceFromLine(char *line)
{
    const char delimiter[2] = ",";
    char *tokens = strtok(line, delimiter);
}

HousePrice *loadHousePricesFromCsv()
{
    int n_training = 1899;
    FILE *stream = fopen("examples/data/house_prices.csv", "r");
    if (stream == NULL)
    {
        perror("Unable to open the file.");
        exit(1);
    }
    char line[1024];
    HousePrice *train_set = malloc(sizeof(HousePrice) * n_training);
    int line_number = 0;

    while (fgets(line, 1024, stream))
    {
        if (line_number > 0)
        {
            char *token = strtok(line, ",");
            int column = 1; // Start from the first column
            float firstColumn, thirdColumn;

            while (token != NULL)
            {
                if (column == 1)
                {
                    firstColumn = atof(token);
                }
                else if (column == 3)
                {
                    thirdColumn = atof(token);
                    break; // No need to tokenize further
                }
                token = strtok(NULL, ",");
                column++;
            }
            HousePrice house_price = {.price = firstColumn, .area = thirdColumn};
            train_set[line_number] = house_price;
        }
        line_number++;
    }
    return train_set;
}

void calculateRegression()
{
    HousePrice *house_prices = loadHousePricesFromCsv();
    int n_training = 1400;
    int n_validation = 400;
    // Träningsdata
    double x[n_training];
    double y[n_training];

    for (int i = 0; i < n_training; i++)
    {
        x[i] = house_prices[i].area;
        y[i] = house_prices[i].price;
    }

    double *values = linearRegression(x, y, n_training);

    printf("k=%f, m=%f", values[0], values[1]);

    // Evaluation

    double *yPred = malloc(sizeof(double) * n_validation);
    for (int i = 0; i < n_validation; i++)
    {
        yPred[i] = (house_prices[i + n_training].area * values[0]) + values[1];
    }
    printf("First prediction real value: %f, predicted value: %f", house_prices[1400].price, yPred[0]);
    double r2 = r2Score(y, yPred, n_validation);
    printf("R2 score: %f", r2);
}