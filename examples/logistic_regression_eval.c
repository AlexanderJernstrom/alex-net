#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "logistic_regression_eval.h"
#include "../regression/logistic_regression.h"

TitanicSurvivor *loadTrainDataFromCsv()
{
    int n_training = 890;
    FILE *stream = fopen("examples/data/titanic_train.csv", "r");
    if (stream == NULL)
    {
        perror("Unable to open the file.");
        exit(1);
    }
    char line[1024];
    TitanicSurvivor *train_set = malloc(sizeof(TitanicSurvivor) * n_training);
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
                if (column == 2)
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
            TitanicSurvivor survivor = {.survived = firstColumn, .pClass = thirdColumn};
            train_set[line_number] = survivor;
        }
        line_number++;
    }
    return train_set;
}

void calculateLogisticRegression()
{
    TitanicSurvivor *train_data = loadTrainDataFromCsv();
    int n_training = 890;

    double x[n_training];
    double y[n_training];

    for (int i = 0; i < n_training; i++)
    {
        x[i] = train_data[i].pClass;
        y[i] = train_data[i].survived;
    }

    double *parameters = logisticRegression(x, y, n_training);

    printf("\n %f * x + %f", parameters[0], parameters[1]);
}